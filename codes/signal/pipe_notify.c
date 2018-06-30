#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mqueue.h>
#include <errno.h>

int pipefd[2];
void sig_usr(int signo);
void Perror(const char *msg);
void err_quit(const char *);

int main(int argc, char **argv)
{
    ssize_t n;
    mqd_t mqd;
    struct sigevent sigev;
    struct mq_attr attr;
    void *buff;
    fd_set rset;

    if(argc < 2)
        err_quit("usage: notify <path>");

    mqd = mq_open(argv[1], O_RDONLY|O_NONBLOCK);
    if(mqd < 0)
        Perror("open mq fail");

    mq_getattr(mqd, &attr);
    buff = malloc(attr.mq_msgsize);

    signal(SIGUSR1, sig_usr);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    mq_notify(mqd, &sigev);

    int ret;
    ret = pipe(pipefd);
    if(ret < 0)
        Perror("call pipe fail");

    FD_ZERO(&rset);
    int nfds;
    char c;
    for(;;)
    {
        FD_SET(pipefd[0], &rset);
        nfds = select(pipefd[0]+1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(pipefd[0], &rset))
        {
            read(pipefd[0], c, 1);
            mq_notify(mqd, &sigev);
            while( (n = mq_receive(mqd, buff, attr.mq_msgsize, NULL)) > 0)
                printf("read %ld bytes\n", (long)n);
            if(errno != EAGAIN)
                err_quit("mq_receive error");
        }
        
    }


    
}

void err_quit(const char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void sig_usr(int signo)
{

    write(pipefd[1], " ", 1);
    return;
}

void Perror(const char *msg)
{
    perror(msg);
    exit(1);
}
