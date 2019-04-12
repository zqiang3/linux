#include "apue.h"
#include <sys/uio.h>

int main(int argc, char **argv)
{
    char *s1 = "hello";
    char *s2 = "world";

    struct iovec iov[2];
    ssize_t nw;

    iov[0].iov_base = s1;
    iov[0].iov_len = strlen(s1);
    iov[1].iov_base = s2;
    iov[1].iov_len = strlen(s2);

    nw = writev(STDOUT_FILENO, iov, 2);
    printf("\n%ld bytes written\n", nw);

    exit(EXIT_SUCCESS);
}
