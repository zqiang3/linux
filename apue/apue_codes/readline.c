#include "apue.h"

int main(int argc, char **argv)
{
    int fd = open("temp", O_RDWR | O_CREAT, 0644);
    if (fd < 0)
        err_sys("open");

    char buf[1024];
    int ret = readline(fd, buf, atoi(argv[1]));
    if (ret < 0)
        err_sys("readline");

    puts(buf);

    return 0;
}
