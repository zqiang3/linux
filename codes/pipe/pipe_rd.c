#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t newpid;
    int fd[2];
    char buf[1000];

    pipe(fd);
    printf("pipe_r fd: %d\n", fd[0]);
    printf("pipe_w fd: %d\n", fd[1]);

    newpid = fork();
    if (newpid < 0)
    {
        printf("fork exception\n");
        exit(1);
    }
    else if (newpid == 0)  // child
    {
        close(fd[1]);  // close write fd
        int len = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        close(fd[0]);  // need to close fd manually

    }
    else  // parent
    {
        close(fd[0]);  // close read fd
        char *text = "hello, world";
        write(fd[1], text, strlen(text));
        close(fd[1]);
    }
    return 0;
}
