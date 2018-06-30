#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

void sig_int(int);
void pr_mask(const char *);
void oops(void *);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    pr_mask("before catching signal, mask sig:");

    if(signal(SIGINT, sig_int) == SIG_ERR)
        oops("signal");

    while(1)
        sleep(3);

    pr_mask("after catching signal, mask sig :");

    return 0;
}

void sig_int(int signo)
{
    pr_mask("in signal, handler");
}


void pr_mask(const char *str)
{
    sigset_t set;
    int errno_save;

    errno_save = errno;

    if(sigprocmask(0, NULL, &set) == -1)
        oops("sigmask");

    printf("enter %s\n", str);
    if(sigismember(&set, SIGQUIT))
        printf("SIGQUIT");
    if(sigismember(&set, SIGINT))
        printf("SIGINT");
    if(sigismember(&set, SIGUSR1))
        printf("SIGUSR1");
    if(sigismember(&set, SIGALRM))
        printf("SIGALRM");

    errno = errno_save;
}

void oops(void *msg)
{
    perror(msg);
    exit(1);
}
