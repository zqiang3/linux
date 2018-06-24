#define FIFO1 "/tmp/fifo.h"
int main(void)
{
    int readfd, writefd;
    pid_t childpid;
    int ret;
    ret = mkfifo(FIFO1, FILE_MODE);
    if(ret < 0 && errno != EEXIST)
        perror("can't create %s", FIFO1);
    ret = mkfifo(FIFO2, FILE_MODE);
    if(ret < 0 && errno != EEXIST)
        perror("can't create %s", FIFO2);

    childpid = fork();
    if(childpid < 0)
    {
        perror("fork error!");
        exit(1);
    }
    else if(childpid == 0)  // child
    {
        readfd = open(FIFO1, O_RDONLY, 0);
        writefd = oepn(FIFO2, O_WRONLY, 0);
        serfver(readfd, writefd);
        exit(1);
    }
    else  // parent
    {
        writefd = open(FIFO1, O_RDONLY, 0);
        readfd = oepn(FIFO2, O_WRONLY, 0);
        client(readfd, writefd)

        waitpid(childpid, NULL, 0);
        close(readfd);
        close(writefd);
        unlink(FIFO1);
        unlink(FIFO2);
    }

    return 0;
}
