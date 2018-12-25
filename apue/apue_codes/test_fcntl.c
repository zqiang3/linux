
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        puts("Usage: ./test <fd>");
        exit(1);
    }

    int fd;
    int flag;
    fd = atoi(argv[1]);
    // fd = open("temp", O_RDONLY);
    flag = fcntl(fd, F_GETFL);
    if(flag < 0)
    {
        perror("fcntl F_GETFL");
        exit(1);
    }

    switch(flag & O_ACCMODE)
    {
        case O_RDONLY:
            printf("read only.\n");
            break;

        case O_WRONLY:
            puts("write only");
            break;
        case O_RDWR:
            puts("read & write");
            break;
        default:
            puts("unknown access mode");
    }

    if(flag & O_APPEND)
        puts("APPEND");

    return 0;
}
