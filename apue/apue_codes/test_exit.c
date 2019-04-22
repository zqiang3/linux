#include "apue.h"

int main(void)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
        err_sys("fork");
    else if (pid == 0)  // child
    {
        printf("this is _exit test\n");
        printf("_exit printf content in the buffer");
        _exit(0);
    }
    else
    {
        printf("this is exit test\n");
        printf("exit printf content in the buffer");
        exit(0);
    }
}
