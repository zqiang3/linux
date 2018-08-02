#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>

void show_attr(int mqid, struct msqid_ds info)
{
    int ret;
    sleep(1);
    ret = msgctl(mqid, IPC_STAT, &info);
    if(-1 == ret)
    {
        perror("fail to get message info");
        exit(1);
    }
    printf("\n");
    printf("bytes number: %d\n", (int)info.msg_cbytes);
    printf("message number: %d\n", (int)info.msg_qnum);
    printf("max bytes number: %d\n", (int)info.msg_qbytes);
    printf("last process send: %d\n", (int)info.msg_lspid);
    printf("last process receive:  %d\n", (int)info.msg_lrpid);
    printf("last time send:  %d\n", (int)info.msg_stime);
    printf("last time receive:  %d\n", (int)info.msg_rtime);
    printf("last time change:  %d\n", (int)info.msg_ctime);
    printf("last uid: %d\n", info.msg_perm.uid);
    printf("last gid: %d\n", info.msg_perm.gid);
}

void println(const char *ptr)
{
    printf("%s\n", ptr);
}
int main(int argc, char **argv)
{
    int ret;
    int flags, mqid;
    key_t key;
    struct msgmbuf{
        int mtype;
        char mtext[10];
    };

    struct msqid_ds info;
    struct msgmbuf buff;
    char *msgpath = argv[1];
    printf("path : %s\n", msgpath);

    key = ftok(msgpath, 'b');
    if(key != -1)
    {
        printf("create key success\n");
        printf("key: 0x%x\n", (int)key);
        
    }
    else
    {
        printf("fail to create the key\n");
        exit(1);
    }
    flags = IPC_CREAT | IPC_EXCL;
    mqid = msgget(key, flags | 0666);
    if(-1 == mqid)
    {
        perror("msgget error");
        return 0;
    }
    show_attr(mqid, info);

    flags = IPC_NOWAIT;
    buff.mtype = 10;
    char *text = "test message";
    memcpy(buff.mtext, text, strlen(text));
    ret = msgsnd(mqid, &buff, strlen(text), flags);
    if(-1 == ret)
    {
        perror("msgsnd error");
        exit(1);
    }
    printf("after send\n");
    show_attr(mqid, info);


    flags = IPC_NOWAIT | MSG_NOERROR;
    ret = msgrcv(mqid, &buff, 10, 10, flags);
    if(-1 == ret)
    {
        perror("msgrcv error");
        exit(1);
    }
    else
    {
        println("receive msg success");
        printf("the length of the message: %d\n", ret);
    }
    show_attr(mqid, info);
    info.msg_perm.uid = 1000;
    info.msg_perm.gid = 1000;
    info.msg_qbytes = 12345;

    ret = msgctl(mqid, IPC_SET, &info);
    if(-1 == ret)
    {
        perror("msgctl set error");
        exit(1);
    }
    else
    {
        println("ctl queue succes");
    }
    show_attr(mqid, info);

    ret = msgctl(mqid, IPC_RMID, NULL);
    if(-1 == ret)
    {
        perror("msgctl remove error");
        exit(1);
    }
    else
    {
        printf("remove msgqueue success\n");
    }


}
