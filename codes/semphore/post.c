#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("usage: cmd <name>\n");
        exit(1);
    }

    int flags;
    sem_t *sem;
    unsigned int value;
    value = 1;

    char *path = argv[1];
    flags = O_RDWR | O_CREAT;
    sem = sem_open(argv[1], flags, 0666, value);

    sem_post(sem);

    int val;
    sem_getvalue(sem, &val);
    printf("sem val: %d\n", val);

    sem_close(sem);

    return 0;
}
