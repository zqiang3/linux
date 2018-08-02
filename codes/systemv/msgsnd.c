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
void println(const char *ptr)
{
    printf("%s\n", ptr);
}

int main(int argc, char **argv)
{
    if(argc < 4)
    {
        printf("Usage: send <path> <type> <info>");
        exit(1);
        
    }

    int ret;
    char *path = argv[1];
    int type = atoi(argv[2]);
    char *info = argv[3];
    key_t key = ftok(path, 'b');
    if(key < 0)
        err_quit("ftok failed");
    else
        printf("key: 0x%x\n", key);

    int open_mode = 0666 | IPC_CREAT;
    int mqid = msgget(key, open_mode);
    if(mqid < 0)
        err_quit("open mqueue failed");
    else
        printf("mqid: %d\n", mqid);

    struct msgmbuf buff;
    buff.mtype = 1;
    int msg_len = strlen(info) + 1;
    memcpy(buff.mtext, info, msg_len);
    ret = msgsnd(mqid, &buff, msg_len, 0);
    if(ret < 0)
        err_quit("send msg failed");
    else
        println("send msg success");

    return 0;
}


void err_quit(const char *info)
{
    perror(info);
    exit(1);
}

