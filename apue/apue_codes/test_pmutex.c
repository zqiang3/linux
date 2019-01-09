#include "apue.h"
#include <pthread.h>

int glob = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *foo(void *args)
{
    
    int MAX = *(int *)args;
    printf("Enter foo\n");
    int i;
    int temp;
    for (i = 0; i < MAX; i++)
    {
        //pthread_mutex_lock(&lock);
        temp = glob;
        temp++;
        glob = temp;
        //pthread_mutex_unlock(&lock);
        
    }
        
    return NULL;
}

int main(int argc, char **argv)
{

    int max = atoi(argv[1]);
    pthread_t tid, tid2;
    pthread_create(&tid, NULL, foo, &max);
    pthread_create(&tid2, NULL, foo, &max);
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);

    printf("glob = %d\n", glob);
    return 0;
}
