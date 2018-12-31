#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
static void sig_alarm(int signo);

unsigned int
sleep1(unsigned int sec)
{
    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        return (sec);

    alarm(sec);
    pause();
    return alarm(0);
}

static void
sig_alarm(int signo)
{
    
}

int main(void)
{
    int a = 5;
    sleep1(5);
    printf("hello, 2019\n");
}
