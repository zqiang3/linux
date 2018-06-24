#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO "/tmp/fifo.server"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MAX 1024

int main(void)
{
    int ret;
    pid_t pid;
    char filename[MAX], buff[MAX];
    char *ptr;
    int len;
    int n;

    int readfd, writefd;


    pid = getpid();
    snprintf(filename, sizeof(filename), "/tmp/fifo.%d", pid);
    ret = mkfifo(filename, FILE_MODE);
    if(ret < 0 && errno != EEXIST)
        exit(1);

    snprintf(buff, sizeof(buff), "%ld ", (long)pid);
    len = strlen(buff);
    ptr = buff + len;

    fgets(ptr, MAX - len, stdin);
    len = strlen(buff);
    ret = mkfifo(FIFO, FILE_MODE);
    if(ret < 0 && errno != EEXIST)
        exit(1);

    
    writefd = open(FIFO, O_WRONLY, 0);
    write(writefd, buff, len);

    readfd = open(filename, O_RDONLY, 0);

    while( (n = read(readfd, buff, MAX)) > 0)
        write(STDOUT_FILENO, buff, n);

    close(readfd);
    unlink(filename);

    return 0;

}
