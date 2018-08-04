#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid, pw;
    int n = 10;
    pid = fork();
    if(pid < 0)
    {
        puts("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("this is child process, pid: %d\n", getpid());
        sleep(10);
        exit(1);
    }
    else
    {
        pid_t parent_pid = getpid();

        while(1)
        {
            printf("I am parent %d\n", parent_pid);
            pw = wait(NULL);
            printf("wait for child %d\n", pw);
            sleep(1);
        }
    }

    exit(0);
}
