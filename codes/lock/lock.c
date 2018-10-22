#include "lock.h"



int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return fcntl(fd, cmd, &lock);
}

void file_lock(int fd)
{
    
    int tempfd;
    while((tempfd = open(LOCKFILE, O_RDWR | O_CREAT | O_EXCL, 0666)) < 0)
    {
        if(errno != EEXIST)
        {
            perror("open file error");
            exit(1);
        }
    }
    close(tempfd);
}

void file_unlock(int fd)
{
    unlink(LOCKFILE);
}

