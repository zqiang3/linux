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
    struct mymesg new_buff;
    ret = mesg_recv(mqid, &new_buff);
    if(ret < 0)
        err_quit("receive msg failed");
    else
    {
        println("receive msg success");
        printf("msg data: %s\n", new_buff.mesg_data);
        printf("msg length: %ld\n", new_buff.mesg_len);
        printf("msg type: %ld\n", new_buff.mesg_type);
    }

    return 0;
}
