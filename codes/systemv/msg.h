#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgmbuf{
    int mtype;
    char mtext[10];
};

void err_quit(const char*);
int open_msg(const char *path);
void println(const char *ptr);
