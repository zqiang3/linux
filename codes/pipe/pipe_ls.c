#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if (pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    }
    else
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    }

    return 0;
}
