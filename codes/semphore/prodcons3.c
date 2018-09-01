#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#define NBUFF 10
#define SEM_MUTEX  "mutex"
#define SEM_NEMPTY "empty"
#define SEM_NSTORED "stored"

struct {
    int buff[NBUFF];
    sem_t mutex, nempty, nstored;
} shared;

int nitems;

void *produce(void *arg);
void *consume(void *arg);


int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("usage: cmd <items>\n");
        exit(1);
    }

    nitems = atoi(argv[1]);

    int flag = O_CREAT;
    int mode = 0666;

    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nempty, 0, NBUFF);
    sem_init(&shared.nstored, 0, 0);

    pid_t tid_produce, tid_consume;
    pthread_create(&tid_produce, NULL, produce, NULL);
    pthread_create(&tid_consume, NULL, consume, NULL);
    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);

    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nempty);
    sem_destroy(&shared.nstored);

    return 0;
}

void *produce(void *arg)
{
    int i;
    struct timeval now;
    int val_mutex, val_nempty, val_nstored;
    for(i = 0; i < nitems; i++)
    {
        sem_wait(&shared.nempty);
        sem_wait(&shared.mutex);

        printf("put i=%d to buff\n", i);
        gettimeofday(&now, NULL);
        //printf("time: %ld %ld\n", now.tv_sec, now.tv_usec);
        shared.buff[i % NBUFF] = i;
        
        sem_post(&shared.mutex);
        sem_post(&shared.nstored);

        sem_getvalue(&shared.mutex, &val_mutex);
        sem_getvalue(&shared.nempty, &val_nempty);
        sem_getvalue(&shared.nstored, &val_nstored);
        printf("mutex=%d, nstored=%d, nempty=%d\n", val_mutex, val_nstored, val_nempty);
    }

    return NULL;
}

void *consume(void *arg)
{
    int i;
    struct timeval now;
    int val_mutex, val_nempty, val_nstored;
    for(i = 0; i < nitems; i++)
    {
        sem_wait(&shared.nstored);
        sem_wait(&shared.mutex);

        printf("test, i=%d\n", i);
        gettimeofday(&now, NULL);
        //printf("time: %ld %ld\n", now.tv_sec, now.tv_usec);
        if(shared.buff[i % NBUFF] != i)
            printf("error, i: %d\n", i);

        sem_post(&shared.mutex);
        sem_post(&shared.nempty);

        sem_getvalue(&shared.mutex, &val_mutex);
        sem_getvalue(&shared.nempty, &val_nempty);
        sem_getvalue(&shared.nstored, &val_nstored);
        printf("mutex=%d, nstored=%d, nempty=%d\n", val_mutex, val_nstored, val_nempty);
    }

    return NULL;
}
