#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid, pw;
    pid = fork();
    if(pid < 0)
    {
        puts("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("this is child process, pid: %d\n", getpid());
        sleep(60);
        exit(1);
    }
    else
    {
        printf("parent process: %d\n", getpid());
        pw = wait(NULL);
        printf("catch a child process, pid is %d\n", pw);
    }

    exit(0);
}
