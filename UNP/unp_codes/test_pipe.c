#include "apue.h"

#define BUF_SIZE 1024

void server(int readfd, int writefd)
{
    char buff[BUF_SIZE];
    ssize_t n;
    ssize_t nread;

    nread = read(readfd, buff, BUF_SIZE);
    if (nread <= 0)
        err_sys("read pipe");

    buff[nread] = '\0';
    int fd = open(buff, O_RDONLY);
    if (fd < 0)
    {
        n = nread;
        snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
        n = strlen(buff);
        write(writefd, buff, n);
    }
    else
    {
        while ( (n = read(fd, buff, BUF_SIZE)) > 0)
            write(writefd, buff, n);

        Close(fd);
    }
}

void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buff[BUF_SIZE];

    fgets(buff, BUF_SIZE, stdin);
    len = strlen(buff);
    if (buff[len - 1] == '\n')
        len--;

    write(writefd, buff, len);

    while ( (n = read(readfd, buff, BUF_SIZE)) > 0)
        write(STDOUT_FILENO, buff, n);
}

int main(void)
{
    int pipe1[2], pipe2[2];

    int ret;
    ret = pipe(pipe1);
    if (ret == -1)
        err_sys("pipe");
    ret = pipe(pipe2);
    if (ret == -1)
        err_sys("pipe");

    pid_t pid = fork();
    if (pid < 0)
        err_sys("fork");
    else if (pid == 0)  // child
    {
        Close(pipe1[0]);
        Close(pipe2[1]);
        server(pipe2[0], pipe1[1]);
        exit(0);
    }
    else if (pid > 0)  // parent
    {
        Close(pipe2[0]);
        Close(pipe1[1]);
        client(pipe1[0], pipe2[1]);
    }

    waitpid(pid, NULL, 0);
    exit(EXIT_SUCCESS);
}
