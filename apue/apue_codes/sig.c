#include "apue.h"
#include <signal.h>

static void sig_usr(int signo)
{
    if (signo == SIGUSR1)
        puts("receive SIGUSR1");
    else if (signo == SIGUSR2)
        puts("receive SIGUSR2");
    else
        printf("receive signal %d\n", signo);
}

int main()
{
    void *p;
    p = signal(SIGKILL, sig_usr);
    if (p== SIG_ERR)
       err_sys("signal");

    for ( ; ; )
        pause();
}
