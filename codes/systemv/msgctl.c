#include "msg.h"



void remove_queue(int);

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("usage: ctl <pathname> <cmd>\n");
        println("args less than 4");
        exit(1);
        
    }

    char *path = argv[1];
    int type = atoi(argv[2]);
    int mqid = open_msg(path);
    if(mqid < 0)
        err_quit("open msg fail");
        
        //msgctl(msqid, IPC_STAT, &info);
        //printf("read-write:%d, cbytes: %d, qnum=%d, qbytes=%d\n",
        //info.msg_perm.mode & 0777, info.msg_cbytes,
        //info.msg_qnum, info.msg_qbytes);

    if(strcmp(argv[2], "remove") == 0)
        remove_queue(mqid);

    printf("here\n");

    return 0;
}

void remove_queue(int mqid)
{
    int ret = msgctl(mqid, IPC_RMID, NULL);
    if(ret < 0)
    {
        perror("remove queue failed");
        exit(1);
    }
    else
        println("remove queue done");
}


