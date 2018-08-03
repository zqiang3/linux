#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_MAX 8092
#define SVMSG_MODE 0644
#define MQ_KEY1 0x62015b4f

struct msgmbuf{
    long mtype;
    char mtext[MSG_MAX];
};

struct mymesg{
    long mesg_len;
    long mesg_type;
    char mesg_data[MSG_MAX];
};

void err_quit(const char*);
int open_msg(const char *path);
void println(const char *ptr);
ssize_t mesg_recv(int, struct mymesg*);
ssize_t mesg_send(int, struct mymesg*);
