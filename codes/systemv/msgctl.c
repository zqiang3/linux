#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/ipc.h>
#include <linux/msg.h>
#include <sys/types.h>

struct msgmbuf{
    int mtype;
    char mtext[10];
};


void remove_queue(int);
void err_quit(const char*);
void println(char *ptr)
{
    printf("%s\n", ptr);
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("usage: ctl <pathname> <cmd>\n");
        println("args less than 4");
        exit(1);
        
    }
    else
    {
        char *path = argv[1];
        int type = atoi(argv[2]);
        key_t key = ftok(path, 'b');
        int open_mode = 0666 | IPC_CREAT;
        struct msgmbuf buf;
        struct msqid_ds info;
        int msqid = msgget(key, open_mode);
        printf("msqid: %d, key: %x\n", msqid, key);
        
        //msgctl(msqid, IPC_STAT, &info);
        //printf("read-write:%d, cbytes: %d, qnum=%d, qbytes=%d\n",
        //info.msg_perm.mode & 0777, info.msg_cbytes,
        //info.msg_qnum, info.msg_qbytes);


        if(strcmp(argv[2], "remove") == 0)
            remove_queue(msqid);

        printf("here\n");

        return 0;
        
    }


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


void err_quit(const char *info)
{
    printf("%s\n", info);
    exit(1);
}
