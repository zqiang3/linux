#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>

struct msgmbuf{
    int mtype;
    char mtext[10];
};

void *memcpy2(void *dest, void *src, unsigned int size);
void send_msg(int mqid, struct msqid_ds info);
void receive_msg(int mqid, struct msqid_ds info);
void change_msg(int mqid, struct msqid_ds info);

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
    printf("===============info================\n");
    printf("ipc perm: %04o\n", info.msg_perm.mode & 0777);
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
    printf("===============info================\n");
    printf("\n");
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

    struct msqid_ds info;
    struct msgmbuf buff;
    if(argc < 3)
    {
        println("usage: ./test <path> <cmd>");
        exit(0);
    }

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
    flags = IPC_CREAT;
    mqid = msgget(key, flags | 0666);
    if(-1 == mqid)
    {
        perror("msgget error: ");
        exit(1);
    }
    else
    {
        println("open queue success");
        printf("mqid: %d\n", mqid);
    }

    show_attr(mqid, info);

    if(strcmp(argv[2], "send") == 0)     // send msg
        send_msg(mqid, info);
    if(strcmp(argv[2], "receive") == 0)  // receive msg
        receive_msg(mqid, info);
    if(strcmp(argv[2], "ctl") == 0)      // receive msg
        change_msg(mqid, info);  

    return 0;
}

void send_msg(int mqid, struct msqid_ds info)
{
    struct msgmbuf buff;
    
    buff.mtype = 10;
    char *text = "test ha";
    memcpy2(buff.mtext, text, strlen(text)+1);
    printf("buff text: %s\n", buff.mtext);
    int msg_sflags = IPC_NOWAIT;
    int ret;
    ret = msgsnd(mqid, &buff, strlen(text)+1, msg_sflags);
    if(ret < 0)
    {
        perror("msg send error");
        exit(1);
    }
    show_attr(mqid, info);
}

void receive_msg(int mqid, struct msqid_ds info)
{
    struct msgmbuf buff;
    int msg_rflags = IPC_NOWAIT | MSG_NOERROR ;
    int ret = msgrcv(mqid, &buff, 10, 0, msg_rflags);
    if(ret < 0)
    {
        perror("msg receive error");
        exit(1);
    }
    else
    {
        printf("receive msg success\n");
        printf("the length of msg: %d\n", ret);
        printf("text: %s\n", buff.mtext);
    }
    show_attr(mqid, info);
}

void change_msg(int mqid, struct msqid_ds info)
{
    info.msg_perm.uid = 1000;
    info.msg_perm.gid = 1000;
    info.msg_qbytes = 12345;
    int ret = msgctl(mqid, IPC_SET, &info);
    show_attr(mqid, info);
}


void *memcpy2(void *dest, void *src, unsigned int size)
{
    if(dest == NULL || src == NULL)
        return NULL;

    int i = 0;
    char *dest1 = (char *)dest;
    char *src1 = (char *)src;
    while(size-- > 0)
    {
        *dest1 = *src1;
        dest1++;
        src1++;
    }
    return dest;
}
