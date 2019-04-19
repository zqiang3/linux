#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

void err_sys(const char* msg);
ssize_t readline(int fd, char *ptr, size_t n);

