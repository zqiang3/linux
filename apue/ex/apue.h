#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/stat.h>

void err_sys(const char *s)
{
    printf("%s\n", s);
    exit(-1);
}


void println(const char *s)
{
    printf("%s\n", s);
}



void
pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status), "");
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
