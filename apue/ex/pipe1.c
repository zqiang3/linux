#include "apue.h"
#include <sys/wait.h>
#define MAX 1024

int
main(int argc, char *argv[])
{
    int fd[2];
    pid_t pid;
    char line[MAX];

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0) {  // parent
        close(fd[0]);
        int fp;
        fp = fopen(argv[1], "r");
        if (fp == NULL)
            err_sys("fopen error");

        int n;
        while (fgets(fp, line, MAX) != NULL)
        {
            n = strlen(line);
            write(fd[1], line, n);
        }

        exit(0);
    }

    close(fd[1]);
    dup2(fd[0], STDOUT_FILENO);

    execl("/bin/usr/more", "more", NULL);
    exit(0);
}
