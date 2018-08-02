#include "msg.h"

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Usage: read <path> <type>");
        exit(1);
        
    }

    int ret;
    char *path = argv[1];
    int type = atoi(argv[2]);
    printf("type: %d\n", type);
    int mqid = open_msg(path);
    if(mqid == -1)
        err_quit("open msg failed");

    struct msgmbuf buff;
    int flag = IPC_NOWAIT;
    ret = msgrcv(mqid, &buff, 10, type, flag);
    if(ret < 0)
        err_quit("receive msg failed");
    else
    {
        println("receive msg success");
        printf("msg: %s\n", buff.mtext);
    }

    return 0;
}
