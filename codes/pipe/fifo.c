#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MAX 1024

void client(int, int);
void server(int, int);

int main(void)
{
    int readfd, writefd;
    pid_t childpid;
    int ret;
    ret = mkfifo(FIFO1, FILE_MODE);
    if(ret < 0 && errno != EEXIST)
        perror("create error!");
    ret = mkfifo(FIFO2, FILE_MODE);
    if(ret < 0 && errno != EEXIST)
        perror("create error!");

    printf("make two fifo success!\n");

    childpid = fork();
    if(childpid < 0)
    {
        perror("fork error!");
        exit(1);
    }
    else if(childpid == 0)  // child
    {
        printf("here is child.\n");
        readfd = open(FIFO1, O_RDONLY, 0);
        writefd = open(FIFO2, O_WRONLY, 0);
        server(readfd, writefd);
        exit(1);
    }
    else  // parent
    {
        printf("here is parent.\n");
        writefd = open(FIFO1, O_WRONLY, 0);
        readfd = open(FIFO2, O_RDONLY, 0);
        client(readfd, writefd);

        waitpid(childpid, NULL, 0);
        close(readfd);
        close(writefd);
        unlink(FIFO1);
        unlink(FIFO2);
    }

    return 0;
}

void client(int readfd, int writefd)
{
    printf("enter client\n");
    size_t len;
    char buff[MAX];
    int n;

    printf("prompt: input file name\n");
    fgets(buff, MAX, stdin);
    len = strlen(buff);
    if(buff[len-1] == '\n')
        len--;
    printf("the path you entered is: %s\n", buff);

    write(writefd, buff, len);
    printf("write path finished\n");
    while((n = read(readfd, buff, MAX)) > 0)
    {
        printf("n: %d\n", n);
        write(STDOUT_FILENO, buff, n);
    }

}

void server(int readfd, int writefd)
{
    printf("enter server\n");
    int fd;
    int n;
    char buff[MAX]; 

    n = read(readfd, buff, MAX);
    if(n == 0)  // reach end-of_file or no data
    {
        perror("read no data");
        exit(1);
    }

    buff[n] = '\0';
    printf("server read path name is: %s\n", buff);
    fd = open(buff, O_RDONLY);
    if (fd < 0)
        perror("open error!");
    else
    {
        printf("server here\n");
        while( (n = read(fd, buff, MAX)) > 0)
        {
            printf("n: %d\n", n);
            write(writefd, buff, n);
        }
        close(fd);
    }
}
