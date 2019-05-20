#include "apue.h"

void sig_int(int signo)
{
    pr_mask("sig_int");
}

int main()
{

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal");

    sigset_t newmask, oldmask, waitmask;

    sigemptyset(&newmask);
    sigemptyset(&waitmask);

    sigaddset(&newmask, SIGINT);
    sigaddset(&waitmask, SIGUSR1);

    pr_mask("original mask");

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) != 0)
        err_sys("sigprocmask");

    pr_mask("after sigprocmask");

    // critical code
    int i = 10;
    while (i--)
    {
        puts("critical code");
        sleep(1);
    }

    sigsuspend(&waitmask);
    pr_mask("after sigsuspend");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) != 0)
        err_sys("sigprocmask");

    pr_mask("after restore sigal mask");

    return 0;
}
