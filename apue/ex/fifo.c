#include "apue.h"

int
main()
{
    int n1, n2;
    n1 = mkfifo("/tmp/fifo.1", 0744);
    if (n1 < 0 && errno != EEXIST)
        err_sys("mkfifo failed");

    n2 = mkfifo("/tmp/fifo.2", 0744);
    if (n2 < 0 && errno != EEXIST)
        err_sys("mkfifo failed");

    pid_t pid;
    pid = fork();
    if (pid < 0)
        err_sys("fork error");

    if (pid == 0)
    {
        int readfd, writefd;
        readfd = open("/tmp/fifo.1", O_RDONLY, 0);
        writefd = open("/tmp/fifo.1", O_WRONLY, 0);
        exit(0);
    }

    sleep(3);

    printf("n2 = %d", n2);
    printf("all finished");
    exit(0);
}
