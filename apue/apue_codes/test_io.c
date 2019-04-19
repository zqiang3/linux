#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "apue.h"

int main(void)
{
    int fd;
    fd = open("temp", O_RDONLY);
    if (fd == -1)
        err_sys("open");
    else
        printf("Open success. fd = %d\n", fd);

    int ret;
    ret = close(fd);
    if (ret == -1)
        err_sys("close");
    else
        puts("close success");

    ret = lseek(STDIN_FILENO, 0, SEEK_SET);
    if (ret == -1)
        err_sys("fseek");
    else
        puts("lseek OK");

    return 0;
}
