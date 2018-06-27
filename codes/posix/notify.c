#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <mqueue.h>
#include <signal.h>
#include <sys/types.h>

void err_quit(const char *info);
void perror_quit(const char *info);

mqd_t mqd;
void *buff;
struct mq_attr attr;
struct sigevent sigev;

static void sig_usr1(int);

int main(int argc, char **argv)
{
    ssize_t n;

    if(argc < 2)
        err_quit("usage: mqnotify <name>");

    mqd = mq_open(argv[1], O_RDONLY);
    if(mqd < 0)
        perror_quit("open mq failed");

    mq_getattr(mqd, &attr);
    buff = malloc(attr.mq_msgsize);

    signal(SIGUSR1, sig_usr1);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    mq_notify(mqd, &sigev);
    for(;;)
        pause();

    return 0;
}

void perror_quit(const char *info)
{
    perror(info);
    exit(1);
}

static void
sig_usr1(int signo)
{
    ssize_t n;
    mq_notify(mqd, &sigev);
    n = mq_receive(mqd, buff, attr.mq_msgsize, NULL);
    if(n < 0)
    {
        perror("receive failure");
    }
    else
        printf("read %ld bytes\n", (long)n);
}
          

void err_quit(const char *info)
{
    printf("%s\n", info);
    exit(1);
}
