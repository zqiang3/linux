#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage ./set <path>\n");
        exit(1);
    }

    int semid;
    int num;
    key_t key = ftok(argv[1], 0);
    if(key < 0)
    {
        perror("ftok failed");
        exit(1);
    }

    int oflag = 0;
    semid = semget(key, 0, oflag);
    if(semid < 0)
    {
        perror("semget failed");
        exit(1);
    }
    union semun semun1;
    struct semid_ds semid1;
    semun1.buf = &semid1;
    semctl(semid, 0, IPC_STAT, semun1);
    int nsems = semun1.buf->sem_nsems;

    printf("nsems = %d\n", nsems);

    unsigned short *ptr;
    ptr = calloc(nsems, sizeof(unsigned short));
    semun1.array = ptr;
    semctl(semid, 0, GETALL, semun1);
    int i;
    for(i = 0; i < nsems; i++)
    {
        printf("semval[%d] = %d\n", i, ptr[i]);
    }

    semctl(semid, 0, SETALL, semun1);

    
}
