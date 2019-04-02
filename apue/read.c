#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 10

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("usage: mkfile <path>");
        exit(1);
    }

    int fd;
    int n;
    char buff[MAX];

    fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    printf("fd=%d\n", fd);
    printf("read content: \n");
    while( (n = read(fd, buff, MAX-1)) > 0)
    {
        buff[n] = '\0';
        printf("%s", buff);
    }

    close(fd);
    return 0;
}

