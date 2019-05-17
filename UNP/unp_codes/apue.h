#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#define BUF_SIZE 1024

void err_sys(const char* msg);
void Close(int);
ssize_t readline(int fd, char *ptr, size_t n);

