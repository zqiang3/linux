#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define SEQFILE "seqno"
#define MAX 8192 

#define read_lock(fd, offset, whence, len) lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define writew_lock(fd, offset, whence, len) lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)

#define un_lock(fd, offset, whence, len) \
    lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);
