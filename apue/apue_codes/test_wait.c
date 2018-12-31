#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "apue.h"

int main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0)
        err_sys("fork");

    if(pid == 0)
    {
        sleep(35);
        exit(10);
    }
    else if(pid > 0)
    {
        int status;
        int ret = wait(&status);
        if(ret > 0 && (status & 0x7f) == 0)
            printf("child exit code: %d\n", (status >> 8) & 0xff);
        else if (ret > 0)
            printf("sig code: %d\n", status & 0x7f);
    }

}
