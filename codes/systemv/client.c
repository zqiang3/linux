#include "msg.h"
void client(int readid, int writeid);

int main(int argc, char **argv)
{
    int mqid;
    mqid = msgget(MQ_KEY1, 0);
    if(mqid < 0)
    {
        perror("open mq error");
        exit(1);
    }
    else
        printf("open mq: %d success\n", mqid);
    client(mqid, mqid);

    return 0;
}

void client(int readid, int writeid)
{

    println("enter client");
    size_t len;
    ssize_t n;
    struct mymesg mesg;
    char *ptr;

    snprintf(mesg.mesg_data, MSG_MAX, "%ld ", (long)getpid());
    len = strlen(mesg.mesg_data);
    ptr = mesg.mesg_data + len;

    println("please enter pathname");
    char *temp = fgets(ptr, MSG_MAX - len, stdin);
    printf("pathname: %s\n", temp);
    len = strlen(mesg.mesg_data);
    if(mesg.mesg_data[len-1] == '\n')
        len--;
    mesg.mesg_len = len;
    mesg.mesg_type = 1;

    mesg_send(writeid, &mesg);
    mesg.mesg_type = getpid();
    while((n = mesg_recv(readid, &mesg)) > 0)
        write(STDOUT_FILENO, mesg.mesg_data, n);
}
