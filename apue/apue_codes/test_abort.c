#include "apue.h"


void self_abort()
{
    printf("enter self abort");

    struct sigaction action;
    if (sigaction(SIGABRT, NULL, &action) != 0)
        err_sys("sigaction");

    if (action.sa_handler == SIG_IGN)
    {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }

    if (action.sa_handler == SIG_DFL)
    {
        printf("fflush stream");
        //fflush(NULL);
    }

    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);

    if (sigprocmask(SIG_SETMASK, &mask, NULL) != 0)
        err_sys("sigprocmask");

    kill(getpid(), SIGABRT);

    //fflush(NULL);
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1);
}

void sig_alarm(int signo)
{
    printf("receive SIGALRM\n");
}

void sig_abort(int signo)
{
    printf("receive SIGABRT");
    //_exit(1);
}


int main()
{
    int i = 10;

    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("signal");
    if (signal(SIGABRT, sig_abort) == SIG_ERR)
        err_sys("signal");

    alarm(100);
    printf("sleep 10 seconds");
    sleep(10);
    printf("after sleep 10 seconds");
    self_abort();
    puts("finished");

}
