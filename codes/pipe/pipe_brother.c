#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    int i;

    pipe(fd);

    for (i=0; i<2; i++)
    {
        if (fork() == 0)
            break;
    }

    if (i == 0)  // first child
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    }
    else if (i == 1)  // second child
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    }
    else
    {
        close(fd[0]);
        close(fd[1]);
        for(i=0; i<2; i++)
            wait(NULL);
    }

    return 0;
}
