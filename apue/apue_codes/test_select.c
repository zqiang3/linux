#include "apue.h"
#include <sys/time.h>
#define BUFSIZE 1024 

int main(void)
{
    fd_set readset;
    int fd = STDIN_FILENO;

    struct timeval tv;

    int retval;
    int isset;
    char buf[BUFSIZE];
    int nread;

    int loops = 0;
    while (1)
    {
        loops++;
        printf("loops = %d\n", loops);
        FD_ZERO(&readset);
        FD_SET(fd, &readset);

        memset(&tv, 0, sizeof(tv));
        tv.tv_sec = 1;
        retval = select(fd + 1, &readset, NULL, NULL, &tv);
        if (retval < 0)
            err_sys("select");
        else if (retval == 0)
            puts("select timeout");
        else if (FD_ISSET(fd, &readset))
        {
            memset(buf, 0, sizeof(buf));
            nread = read(fd, buf, BUFSIZE);
            if (nread > 0)
                puts(buf);
            else if (nread == 0)
                break;
            else
                perror("read");
        }
    }

    return 0;
}
