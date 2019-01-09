#include <stdio.h>
#include <stdlib.h>
void *foo(void *args);

void print_ids()
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("pid = %u, tid = %u, tid=0x%x \n", (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, foo, NULL);
    sleep(3);
    print_ids();
    exit(0);
}

void *foo(void *args)
{
    printf("foo\n");
    print_ids();
}
