```c
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);
// Both return: process ID if OK, 0(see later), or -1 on error

int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
// Returns: 0 if OK, -1 on error

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

pid_t wait3(int *statloc, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage);
// Both return: process ID if OK, 0 or -1 on error
```



## 如何避免产生僵尸进程

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void
pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n",
                WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
                WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core firle generated)" : "");
#else
                "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",
                WSTOPSIG(status));
}

void err_sys(const char* s)
{
    printf("errno=%d, %s", errno, s);
    exit(-1);
}

int main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");

    }
    else if (pid == 0)
    {
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            exit(0);

        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");

    printf("main finished\n");
    exit(0);
}
```





## Example

wait

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void
pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n",
                WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
                WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core firle generated)" : "");
#else
                "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",
                WSTOPSIG(status));
}

void err_sys(const char* s)
{
    printf("errno=%d, %s", errno, s);
    exit(-1);
}

int main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        status /= 0;

    if (wait(&status) != pid)
        err_sys("wait error\n");
    pr_exit(status);

    printf("main finished\n");

    exit(0);
}
```

