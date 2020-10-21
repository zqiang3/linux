#include "apue.h"
#define MAX 1024

int
main(int argc, char *argv[])
{
    int fd[2];
    int n;

    pid_t pid;

    pipe(fd);

    pid = fork();
    if (pid < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        char line[MAX];

        close(fd[1]);
        n = read(fd[0], line, MAX);
        write(STDOUT_FILENO, line, n);
    }

    close(fd[0]);
    write(fd[1], "hello world\n", 12);
    printf("all finished\n");
    exit(0);
}
