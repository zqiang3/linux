#include "apue.h"

void sig_int(int signo)
{
    printf("receive SIGINT");
}


int main()
{
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal");


    sigset_t newset, oldset;
    sigset_t zeroset;
    sigemptyset(&newset);
    sigemptyset(&zeroset);
    sigaddset(&newset, SIGINT);
    int ret;
    ret = sigprocmask(SIG_BLOCK, &newset, &oldset);
    if (ret != 0)
        err_sys("sigprocmask");

    sleep(5);

    if (sigpending(&zeroset) != 0)
        err_sys("sigpending");

    if (sigismember(&zeroset, SIGINT))
        printf("SIGINT PENDING\n");

    if (sigprocmask(SIG_SETMASK, &oldset, NULL) != 0)
        err_sys("sigprocmask");

    printf("unblock SIGINT");
    
}
