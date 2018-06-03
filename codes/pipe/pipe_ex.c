#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


#define MAX 1000
void client(int, int), server(int, int);

int main(void)
{
    int pipe_left[2];
    int pipe_right[2];
    int ret;
    pid_t pid;

    ret = pipe(pipe_left);
    if (ret == -1)
    {
        perror("call pipe failure.\n");
        exit(1);
    }
    ret = pipe(pipe_right);
    if (ret == -1)
    {
        perror("call pipe failure.\n");
        exit(1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("call fork failure.\n");
        exit(1);
    }
    else if (pid == 0)  // child process
    {
        printf("chile pid: %d\n", getpid());
        close(pipe_left[1]);
        close(pipe_right[0]);

        server(pipe_left[0], pipe_right[1]);
        exit(0);
        
    }
    else  // parent process
    {
        printf("parent pid: %d\n", getpid());
        close(pipe_left[0]);
        close(pipe_right[1]);

        client(pipe_right[0], pipe_left[1]);
        waitpid(pid, NULL, 0);
        exit(0);
    }
}

void client(int readfd, int writefd)
{
    size_t len;
    int n;
    char buff[MAX];

    printf("input filename\n");
    fgets(buff, MAX, stdin);
    len = strlen(buff);
    if(buff[len-1] == '\n')
        len--;

    write(writefd, buff, len);

    while((n = read(readfd, buff, MAX)) > 0)
        write(STDOUT_FILENO, buff, n);

}


void server(int readfd, int writefd)
{
    int fd;
    int n;
    char buff[MAX];

    if((n = read(readfd, buff, MAX)) == 0)
    {
        perror("read form pipe error");
        exit(1);
    }

    buff[n] = '\0';
    if((fd = open(buff, O_RDONLY)) < 0)
    {
        perror("open file error");
        exit(1);
    }
    else
    {
        printf("output content\n");
        while((n = read(fd, buff, MAX)) > 0)
            write(writefd, buff, n);
        close(fd);
    }

}
