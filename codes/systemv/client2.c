#include "msg.h"
void client(int readid, int writeid);

int main(int argc, char **argv)
{
    int readid, writeid;
    writeid = msgget(MQ_KEY1, 0);
    if(writeid < 0)
    {
        perror("open mq error");
        exit(1);
    }
    else
        printf("open mq: %d success\n", writeid);

    readid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
        
    client(readid, writeid);

    msgctl(readid, IPC_RMID, NULL);

    return 0;
}

void client(int readid, int writeid)
{

    println("enter client");
    size_t len;
    ssize_t n;
    struct mymesg mesg;
    char *ptr;

    snprintf(mesg.mesg_data, MSG_MAX, "%d ", readid);
    len = strlen(mesg.mesg_data);
    ptr = mesg.mesg_data + len;

    println("please enter pathname");
    fgets(ptr, MSG_MAX - len, stdin);
    printf("pathname: %s\n", ptr);
    len = strlen(mesg.mesg_data);
    if(mesg.mesg_data[len-1] == '\n')
        len--;
    mesg.mesg_len = len;
    mesg.mesg_type = 1;

    mesg_send(writeid, &mesg);
    while((n = mesg_recv(readid, &mesg)) > 0)
        write(STDOUT_FILENO, mesg.mesg_data, n);
}
