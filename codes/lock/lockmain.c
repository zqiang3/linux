#include "lock.h"


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


int main(int argc, char **argv)
{
    int fd;
    long i, seqno;
    pid_t pid;
    ssize_t n;
    char line[MAX];
    int loop;
    struct timeval time_begin, time_end;

    if(argc < 2)
    {
        printf("usage: lock <loop>\n");
        exit(1);
    }

    pid = getpid();
    fd = open(SEQFILE, O_RDWR | O_CREAT, 0666);
    loop = atoi(argv[1]);
    int t1 = time(NULL);
    gettimeofday(&time_begin, NULL);
    for(i = 0; i < loop; i++)
    {
        //file_lock(fd);
        my_lock(fd);

        lseek(fd, 0, SEEK_SET);
        n = read(fd, line, MAX);
        line[n] = '\0';

        n = sscanf(line, "%ld\n", &seqno);
        //printf("%s: pid=%ld, seq# = %ld\n", argv[0], (long)pid, seqno);
        seqno++;

        snprintf(line, sizeof(line), "%ld\n", seqno);
        lseek(fd, 0, SEEK_SET);
        write(fd, line, strlen(line));
        //file_unlock(fd);
        my_unlock(fd);
   }
    gettimeofday(&time_end, NULL);
    printf("time used: %ld sec, %ld usec\n", time_end.tv_sec - time_begin.tv_sec, time_end.tv_usec-time_begin.tv_usec);
    close(fd);
    exit(0);
}
