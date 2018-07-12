#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int gnum = 0;
pthread_mutex_t mutex;

static void func1(void);
static void func2(void);

int main(int argc, char *argv[])
{
    pthread_t pid1, pid2;
    int ret = 0;

    pthread_mutex_init(&mutex, NULL);
    ret = pthread_create(&pid1, NULL, (void *)func1, NULL);
    if (ret != 0)
    {
        perror("create pid1 error");
        exit(1);
    }

    ret = pthread_create(&pid2, NULL, (void *)func2, NULL);
    if (ret != 0)
    {
        perror("create pid2 error");
        exit(1);
    }

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    printf("main programme finished\n");
    return 0;
}

static void func1(void)
{
    int i = 0;
    for(i=0; i<3; i++)
    {
        printf("this is pthread 1\n");
        pthread_mutex_lock(&mutex);
        sleep(1);
        gnum++;
        printf("thread 1 add one to num: %d\n", gnum);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

static void func2(void)
{
    int i = 0;
    for(i=0; i<5; i++)
    {
        printf("this is pthread 2\n");
        pthread_mutex_lock(&mutex);
        sleep(1);
        gnum++;
        printf("thread 2 add one to num: %d\n", gnum);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
