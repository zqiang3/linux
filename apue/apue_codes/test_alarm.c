#include "apue.h"
#include <signal.h>

void sig_alarm(int signo)
{
    puts("received SIG_ALARM");
}

int main()
{
    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("signal");

    unsigned int sec;
    sec = alarm(10);
    pause();
    puts("main exit");
    exit(0);
}
