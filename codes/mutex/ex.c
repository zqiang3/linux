#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct ct_sum
{
    int sum;
    pthread_mutex_t lock;
}ct_sum;

void *add1(void *cnt)
{
    ct_sum *p = (ct_sum*)cnt;
    pthread_mutex_lock(&(p->lock));
    int i;
    for(i=0; i<50; i++)
    {
        printf("add1 i: %d\n", i);
        p->sum += 1;
        sleep(0.05);
    }
    pthread_mutex_unlock(&(p->lock));
    pthread_exit(NULL);
    return 0;
}

void *add2(void *cnt)
{
    ct_sum *p = (ct_sum*)cnt;
    pthread_mutex_lock(&(p->lock));
    int i;
    for(i=51; i<100; i++)
    {
        printf("add2 i: %d\n", i);
        p->sum += 1;
        sleep(0.05);
    }
    pthread_mutex_unlock(&(p->lock));
    pthread_exit(NULL);
    return 0;
}


int main(void)
{
    int i;
    pthread_t pid1, pid2;
    int sum = 0;
    ct_sum cnt;
    pthread_mutex_init(&(cnt.lock), NULL);
    cnt.sum = 0;
    pthread_create(&pid1, NULL, add1, &cnt);
    pthread_create(&pid2, NULL, add2, &cnt);

    pthread_mutex_lock(&(cnt.lock));
    printf("sum %d\n", cnt.sum);
    pthread_mutex_unlock(&(cnt.lock));
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    pthread_mutex_destroy(&(cnt.lock));
    printf("sum %d\n", cnt.sum);
    return 0;
}

