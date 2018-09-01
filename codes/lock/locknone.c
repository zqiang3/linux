#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define SEQFILE "seqno"
#define MAX 8192 

#define read_lock(fd, offset, whence, len) lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define writew_lock(fd, offset, whence, len) lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)

void my_lock(int fd)
{
    writew_lock(fd, 0, SEEK_SET, 0);
    
}

void my_unlock(int fd)
{
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    fcntl(fd, F_SETLKW, &lock);
    return;
}

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return fcntl(fd, cmd, &lock);
}

int main(int argc, char **argv)
{
    int fd;
    long i, seqno;
    pid_t pid;
    ssize_t n;
    char line[MAX];
    int loop;

    if(argc < 2)
    {
        printf("usage: lock <loop>\n");
        exit(1);
    }

    pid = getpid();
    fd = open(SEQFILE, O_RDWR | O_CREAT, 0666);
    loop = atoi(argv[1]);
    for(i = 0; i < loop; i++)
    {
        lseek(fd, 0, SEEK_SET);
        n = read(fd, line, MAX);
        line[n] = '\0';

        n = sscanf(line, "%ld\n", &seqno);
        printf("%s: pid=%ld, seq# = %ld\n", argv[0], (long)pid, seqno);
        sleep(0.1);
        seqno++;

        snprintf(line, sizeof(line), "%ld\n", seqno);
        lseek(fd, 0, SEEK_SET);
        write(fd, line, strlen(line));
    }
    close(fd);
    exit(0);
}
