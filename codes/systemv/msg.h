#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SVMSG_MODE 0644

struct msgmbuf{
    int mtype;
    char mtext[15];
};

void err_quit(const char*);
int open_msg(const char *path);
void println(const char *ptr);
