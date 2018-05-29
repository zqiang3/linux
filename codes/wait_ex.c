#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int count = 0;

    pid_t pid;
    int status = -1;
    
    pid = fork();

    if(pid < 0)
    {
        printf("fork error %m\n", errno);
    }
    else if (pid > 0)  // parent process
    {
        printf("this is parent, pid = %d\n", getpid());
        wait(&status);
    }
    else   // chile process
    {
        printf("this is child, pid = %d, ppid = %d\n", getpid(), getppid());
        int i = 0;
        for (i = 0; i < 10; i++)
        {
            count ++;
            sleep(1);
            printf("count = %d\n", count);
        }
        exit(5);
    }

    printf("child exit status is %d\n", WEXITSTATUS(status));
    printf("end of program from pid = %d\n", getpid());
    return 0;

}
