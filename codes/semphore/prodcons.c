#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#define NBUFF 10
#define MAX_THREADS 100
#define SEM_MUTEX  "mutex"
#define SEM_NEMPTY "empty"
#define SEM_NSTORED "stored"

struct {
    int nput;
    int nputval;
    int nget;
    int ngetval;
    int buff[NBUFF];
    sem_t mutex, nempty, nstored;
} shared;

sem_t print_mutex;

int min(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}


int nitems;
int nproducers;
int nconsumers;

void *produce(void *arg);
void *consume(void *arg);

void print_info(int id, const char *info)
{
    int val_mutex, val_nempty, val_nstored;
    sem_getvalue(&shared.mutex, &val_mutex);
    sem_getvalue(&shared.nempty, &val_nempty);
    sem_getvalue(&shared.nstored, &val_nstored);
    struct timeval now;
    gettimeofday(&now, NULL);
    printf("%ld%ld: id=%d, %s: ", now.tv_sec, now.tv_usec, id, info);
    printf("mutex=%d, nstored=%d, nempty=%d\n", val_mutex, val_nstored, val_nempty);
}


int main(int argc, char **argv)
{
    if(argc < 4)
    {
        printf("usage: cmd <items> <pro_threads> <con_threads>\n");
        exit(1);
    }

    nitems = atoi(argv[1]);
    nproducers = atoi(argv[2]);
    nconsumers = atoi(argv[3]);

    shared.nput = 0;
    shared.nputval = 0;
    shared.nget = 0;
    shared.ngetval = 0;

    sem_init(&print_mutex, 0, 1);
    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nempty, 0, NBUFF);
    sem_init(&shared.nstored, 0, 0);

    pid_t tid_produce[nproducers];
    pid_t tid_consume[nconsumers];
    int count[nproducers];
    int count_cons[nconsumers];
    int i;
    for(i = 0; i < nproducers; i++)
    {
        count[i] = i;
        pthread_create(&tid_produce[i], NULL, produce, &count[i]);
        
    }
    for(i = 0; i < nconsumers; i++)
    {
        count_cons[i] = i;
        pthread_create(&tid_consume[i], NULL, consume, &count_cons[i]);
    }
        
    for(i = 0; i < nproducers; i++)
    {
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }
    for(i = 0; i < nconsumers; i++)
    {
        pthread_join(tid_consume[i], NULL);
        printf("count_cons[%d] = %d\n", i, count_cons[i]);
    }

    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nempty);
    sem_destroy(&shared.nstored);

    return 0;
}

void *produce(void *arg)
{
    int id = (*(int *)arg);
    int *count = (int *)arg;
    *count = 0;
    for(;;)
    {
        sem_wait(&shared.nempty);
        sem_wait(&shared.mutex);

        if(shared.nput >= nitems)
        {
            sem_post(&shared.nempty);
            sem_post(&shared.nstored);
            sem_post(&shared.mutex);
            printf("producer finished\n");
            return NULL; 
        }

        printf("id=%d put i=%d to buff\n", id, shared.nputval);
        shared.buff[shared.nput % NBUFF] = shared.nputval;
        shared.nput++;
        shared.nputval++;
        (*count)++;

        sem_post(&shared.mutex);
        sem_post(&shared.nstored);
    }

    return NULL;
}

void *consume(void *arg)
{
    int id = (*(int *)arg);
    int *count = (int *)arg;
    *count = 0;
    for(;;)
    {
        sem_wait(&shared.nstored);
        sem_wait(&shared.mutex);

        if(shared.nget >= nitems)
        {
            sem_post(&shared.nstored);
            sem_post(&shared.mutex);
            printf("consumer finished\n");
            return NULL;
        }

        printf("id=%d check_value, i=%d\n", id, shared.ngetval);
        if(shared.buff[shared.nget % NBUFF] != shared.ngetval)
            printf("error, i: %d\n", shared.ngetval);

        shared.nget++;
        shared.ngetval++;
        (*count)++;

        sem_post(&shared.mutex);
        sem_post(&shared.nempty);
    }

    return NULL;
}
