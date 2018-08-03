#include "msg.h"

void println(const char *ptr)
{
    printf("%s\n", ptr);
}

void err_quit(const char *info)
{
    perror(info);
    exit(1);
}

int open_msg(const char *path)
{
    
    key_t key = ftok(path, 'b');
    if(key < 0)
    {
        perror("ftok failed");
        return -1;
    }
    else
        printf("key: 0x%x\n", key);

    int open_mode = 0666 | IPC_CREAT;
    int mqid = msgget(key, open_mode);
    if(mqid < 0)
    {
        perror("open mqueue failed");
        return -1;
    }
    else
    {
        printf("mqid: %d\n", mqid);
        return mqid;
    }
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
    ssize_t n;
    n = msgrcv(id, &(mptr->mesg_type), MSG_MAX, mptr->mesg_type, 0);
    mptr->mesg_len = n;

    return n;
}

ssize_t mesg_send(int id, struct mymesg *mptr)
{
    return (msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0));
}
