#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "apue.h"

int glob = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var = 88;
    pid_t pid;
    
    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf)-1)
        err_sys("write error");

    puts("before fork");

    if( (pid = vfork()) < 0)
        err_sys("fork");
    else if (pid == 0)
    {
        glob++;
        var++;
        // the child must not return from the current function or call exit, but may call _exit
        _exit(0);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);

    exit(0);
}
