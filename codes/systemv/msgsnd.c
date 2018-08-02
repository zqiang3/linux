#include "msg.h"


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
    int mqid = open_msg(path);
    if(mqid < 0)
        err_quit("open mqueue failed");

    struct msgmbuf buff;
    buff.mtype = type;
    int msg_len = strlen(info) + 1;
    memcpy(buff.mtext, info, msg_len);
    ret = msgsnd(mqid, &buff, msg_len, 0);
    if(ret < 0)
        err_quit("send msg failed");
    else
        println("send msg success");

    return 0;
}


