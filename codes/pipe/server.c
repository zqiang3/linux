#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define FIFO "/tmp/fifo.server"
#define MAX 1024
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(void)
{
    int ret;
    int fd;
    int readfd, writefd, tempfd;
    char buff[MAX];
    char filename[MAX];
    char *ptr;
    int n;
    pid_t pid;

    ret = mkfifo(FIFO, FILE_MODE);
    if(ret < 0 && errno != EEXIST)
        exit(1);

    readfd = open(FIFO, O_RDONLY, 0);
    tempfd = open(FIFO, O_WRONLY, 0);

    while( (n = read(readfd, buff, MAX)) > 0)
    {
        if(buff[n-1] == '\n')
            n--;
        buff[n] = '\0';

        if((ptr = strchr(buff, ' ')) == NULL)
        {
            perror("bogus request");
            continue;
        }
        *ptr++ = '\0';
        pid = atoi(buff);
        printf("pid: %d comes in\n", pid);
        snprintf(filename, sizeof(filename), "/tmp/fifo.%d", pid);
        writefd = open(filename, O_WRONLY, 0);
        if(writefd < 0 && errno != EEXIST)
            continue;


        fd = open(ptr, O_RDONLY, 0);
        if(fd < 0)
            exit(1);
        else
        {
            while( (n = read(fd, buff, MAX)) > 0)
                write(writefd, buff, n);

            close(fd);
            close(writefd);
        }

    }

    return 0;
}
