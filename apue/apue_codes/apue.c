#include <stdlib.h>

void err_sys(const char* msg)
{
    perror(msg);
    exit(1);
}

ssize_t readline(int fd, char *ptr, size_t n)
{
    
    char c;
    int nread = 0;

    int ret;
    int i;
    for (i = 0; i < n -1; i++)
    {
        ret = read(fd, &c, 1);
        if (ret < 0)
            return -1;
        else if (ret == 0)
            break;
        else
        {
            *ptr++ = c;
            nread++;
        }
    }

    *ptr = 0;
    return nread;
}
