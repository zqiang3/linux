#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

static pid_t *childpid = NULL;
static int maxfd;

FILE *
popen(const char *cmd, const char *type)
{
    int i;
    int pfd[2];
    pid_t pid;
    FILE *fp;

    if (type == NULL) {
        err_sys("type is null");
    }
    if (strlen(type) != 1) {
        err_sys("type invalid");
    }
    if (type[0] != 'r' && type[0] != 'w')
    {
        errno = EINVAL;
        return NULL
    }
}

