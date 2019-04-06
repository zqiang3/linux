#include "apue.h"
#include <sys/wait.h>

int my_system(const char *cmd)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)  // 进程数耗尽
        return (1);
    else if (pid == 0)
    {
        execl("/bin/sh", "sh", "-c", cmd, (char *)0);
        _exit(127);
    }

    int status;
    while (waitpid(pid, &status, 0) == -1)  // if fail
    {
        if (status != EINTR)
        {
            status = -1;
            break;
        }
    }

    return (status);
}

void pre_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", 
            WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
            WTERMSIG(status),
#ifdef WCOREDUMP
            WCOREDUMP(status) ? " (core file generated)" : "");
#else
            "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

void test_wait_status()
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        // exit(7);
        abort();
        //status /= 0;
        exit(127);
    }

    int ret;
    ret = wait(&status);
    if (ret != pid)
        err_sys("wait error");
    pre_exit(status);
}

void test_system()
{
    int status;
    status = my_system("date");
    if (status < 0)
        err_sys("system() error");
    pre_exit(status);

    status = system("nosuchcmd");
    if (status < 0)
        err_sys("system() error");
    pre_exit(status);

    status = system("who; exit 44");
    if (status < 0)
        err_sys("system() error");
    pre_exit(status);

    exit(0);
}

int main(int argc, char **argv)
{
    // test_wait_status();
    test_system();

    exit(0);
}
