#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue.h"

char *env_list[] = 
{
    "USER=unknown",
    "PATH=/tmp",
    NULL
};

int main(int argc, char *argv[])
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork");
    else if(pid == 0)
    {
        if(execle("/home/sparkfly/c/echoall", "echoall", "arg1", "arg2", (char *)0, env_list) < 0)
            err_sys("execle");
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait");

    if ((pid = fork()) < 0)
        err_sys("fork");
    else if (pid == 0)
    {
        if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
            err_sys("execlp");
    }

    exit(0);
}
