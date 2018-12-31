#include <stdio.h>
#include <stdlib.h>

void handler(int sig)
{
    printf("pid: %d get a signal: %d, process exit\n", getpid(), sig);
    exit(1);
}

int main(void)
{
    alarm(5);
    int i;
    for (i = 1; i < 32; i++)
        signal(i, handler);

    int *p = (int *)10;
    // *p = 1;  // SIGSEGV 11
    // abort();  // signal abort 6

    while (1)
    {
        sleep(1);
        printf("hello\n");
    }
}
