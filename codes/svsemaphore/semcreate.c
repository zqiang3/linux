#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

int main(int argc, char ** argv)
{
    if(argc < 3)
    {
        printf("Usage create <path> <num>\n");
        exit(1);
    }
    
    char *path = argv[1];
    key_t key = ftok(path, 0);
    if(key < 0)
    {
        perror("ftok failed");
        exit(1);
    }

    int semid;
    int num = atoi(argv[2]);
    semid = semget(key, num, 0644 | IPC_CREAT);
    if(semid < 0)
    {
        perror("semget failed");
        exit(1);
    }

    printf("semid=%d\n", semid);
    return 0;
}
