#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int glob = 10;

void *foo(void *arg)
{
    int *a = arg;
    puts("foo");
    //glob++;
    (*a)++;
    sleep(1);
    //pthread_exit(NULL);
    //exit(1);
    puts("foo exit");
    return NULL;
}

int main(void)
{
    pthread_t tid;
    pthread_t tid2;
    int a = 5;
    pthread_create(&tid, NULL, foo, &a);
    pthread_create(&tid2, NULL, foo, &a);
    sleep(3);
    printf("glob=%d\n", glob);
    printf("a=%d\n", a);
    puts("main exit");

    return 0;
}
