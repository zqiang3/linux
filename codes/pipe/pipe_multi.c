#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    pid_t pid;
    int fd[2];
    char buf[1024];
    int i, n;

    int pipe_ret = pipe(fd);
    if (pipe_ret == -1)
    {
        perror("pipe error");
        exit(1);
    }

    for (i = 0; i < 2; i++)
    {
        if((pid=fork()) == 0)
            break;
        else if (pid == -1)
        {
            perror("pipe error");
            exit(1);
        }
    }

    char *text1 = "1.hello\n";
    char *text2 = "2.hello\n";

    if (i == 0)  // one child process
    {
        close(fd[0]);
        sleep(1);
        write(fd[1], text1, strlen(text1));
    }
    else if (i == 1)
    {
        close(fd[0]);
        write(fd[1], text2, strlen(text2));
        sleep(5);
    }
    else  // parent process
    {
        close(fd[1]);
        while( (n = read(fd[0], buf, sizeof(buf))) != 0)
        {
            write(STDOUT_FILENO, buf, n);
        }
        printf("result of read pipe is 0 now\n");

        for (i = 0; i < 2; i ++)
            wait(NULL);
    }

    return 0;
}

