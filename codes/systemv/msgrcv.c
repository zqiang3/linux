#include "msg.h"

int main(int argc, char **argv)
{
    println("Usage: read [-q]");
    int mqid = 0;

    char **ptr = argv;
    int i;
    char c;
    for(i=0; i<argc; i++)
    {
        char *p = argv[i];
        if(p[0] == '-' && strlen(p)>1 && p[1] == 'q')
        {
            p += 2;
            mqid = atoi(p);
            printf("specify mqid: %d\n", mqid);
            break;
        }
    }

    int ret;
    if(mqid <= 0)
    {
        char *path = argv[1];
        int type = atoi(argv[2]);
        mqid = open_msg(path);
    }
    if(mqid == -1)
        err_quit("open msg failed");

    struct msgmbuf buff;
    int flag = IPC_NOWAIT;  // non-blocking
    ret = msgrcv(mqid, &buff, MSG_MAX, 0, 0);
    if(ret < 0)
        err_quit("receive msg failed");
    else
    {
        println("receive msg success");
        printf("msg: %s\n", buff.mtext);
    }

    return 0;
}
