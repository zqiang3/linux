#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    int i;
    pid_t pid;


    for (i=0; i<2; i++)
    {
        if ((pid = fork()) == 0)
            break;
        else
            printf("child pid is: %d\n", pid);
    }

    if (i == 0)  // first child
    {
        printf("child %d start\n", i);
        sleep(2);
        printf("child %d end\n", i);
    }
    else if (i == 1)  // second child
    {
        printf("child %d start\n", i);
        sleep(1);
        printf("child %d end\n", i);
    }
    else
    {
        close(fd[0]);
        close(fd[1]);
        int pid = 0;
        for(i=0; i<2; i++)
        {
            pid = wait(NULL);
            printf("wait. child process pid is: %d\n", pid);
        }
    }

    return 0;
}
