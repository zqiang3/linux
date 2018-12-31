#include <stdio.h>
#include <signal.h>
#include "apue.h"
static void sig_usr(int signo);

int main(void)
{
    void (*p)(int);
    p = signal(SIGUSR1, sig_usr);
    if (p == SIG_ERR)
        err_sys("signal");

    while (1)
    {
        printf("hello\n");
        sleep(1);
    }

    return 0;
}

static void
sig_usr(int signo)
{
    if(signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("received SIGUSR2\n");
}
