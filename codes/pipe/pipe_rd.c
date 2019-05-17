#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

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
        errno = 0;
        ssize_t len;
        while ((len = read(fd[0], buf, sizeof(buf))) > 0)
            write(STDOUT_FILENO, buf, len);
            
        close(fd[0]);  // need to close fd manually
    }
    else  // parent
    {
        close(fd[0]);  // close read fd
        int count = 0;
        while (count < 3)
        {
            printf("This is parent process. count: %d\n", count);
            char *text = "Hello, my friend.\n";
            write(fd[1], text, strlen(text));
            printf("write success. count: %d\n", count);
            sleep(0.1);
            count ++;
        }
        close(fd[1]);
    }
    return 0;
}
