#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> 
#include <semaphore.h>
#include <pthread.h>

#define NBUFF 10
#define MAX 1024

struct shared {
    struct {
        char data[MAX];
        int n;
    } buff[NBUFF];
    sem_t sem_mutex, sem_empty, sem_stored;
} shared;
int fd;

void *produce(void *arg);
void *consume(void *arg);

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("usage test <filename>\n");
        exit(1);
    }

    pthread_t tid_produce, tid_consume;
    fd = open(argv[1], O_RDONLY);
    printf("open file success. fd=%d\n", fd);

    sem_init(&shared.sem_mutex, 0, 1);
    sem_init(&shared.sem_empty, 0, NBUFF);
    sem_init(&shared.sem_stored, 0, 0);


    pthread_create(&tid_produce, NULL, produce, NULL);
    pthread_create(&tid_consume, NULL, consume, NULL);

    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);

    sem_destroy(&shared.sem_mutex);
    sem_destroy(&shared.sem_empty);
    sem_destroy(&shared.sem_stored);

    return 0;
}

void *produce(void *arg)
{
    int i = 0;
    int n;
    for(;;)
    {
        sem_wait(&shared.sem_empty);
        //sem_wait(shared.sem_mutex);
        shared.buff[i].n = read(fd, shared.buff[i].data, MAX);
        if(shared.buff[i].n == 0)
        {
            printf("reach file end\n");
            sem_post(&shared.sem_stored);
            return NULL;
        }

        if(++i >= NBUFF)
            i = 0;   // circular

        sem_post(&shared.sem_stored);
        //sem_post(&shared.sem_mutex);
    }
}

void *consume(void *arg)
{
    int i = 0;
    for(;;)
    {
        sem_wait(&shared.sem_stored);
        //sem_wait(shared.sem_mutex);
        if(shared.buff[i].n == 0)
            return NULL;
        write(STDOUT_FILENO, shared.buff[i].data, shared.buff[i].n);
        shared.buff[i].n = 0;
        if(++i >= NBUFF)
            i = 0;

        sem_post(&shared.sem_empty);
        //sem_post(&shared.sem_mutex);
    }
}


