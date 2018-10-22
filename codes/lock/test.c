#include "lock.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("usage: test <path>\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);

    write_lock(fd, 0, SEEK_SET, 0);
    printf("%ld: parent obtain write lock\n", time(NULL));

    if(fork() == 0)
    {
        sleep(2);
        printf("%ld: child1 try to obtain write lock\n", time(NULL));
        writew_lock(fd, 0, SEEK_SET, 0);
        printf("%ld: child1 obtain write lock\n", time(NULL));
        sleep(1);
        un_lock(fd, 0, SEEK_SET, 0);
        printf("%ld: child1 release write lock\n", time(NULL));
        exit(0);
    }
    
    if(fork() == 0)
    {
        sleep(1);
        printf("%ld: child2 try to obtain read lock\n", time(NULL));
        readw_lock(fd, 0, SEEK_SET, 0);
        printf("%ld: child2 obtain read lock\n", time(NULL));
        sleep(1);
        un_lock(fd, 0, SEEK_SET, 0);
        printf("%ld: child2 release read lock\n", time(NULL));
        exit(0);
    }

    sleep(5);
    un_lock(fd, 0, SEEK_SET, 0);
    printf("%ld: parent release write lock\n", time(NULL));
    exit(0);
}
