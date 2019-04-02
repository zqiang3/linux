#include "apue.h"
#include <stdio.h>

void err_sys(const char* msg)
{
    perror(msg);
    exit(1);
}

void *xmalloc(size_t size)
{
    void *p = malloc(size);
    if (!p)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    return p;
}
