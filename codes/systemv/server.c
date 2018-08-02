#include "msg.h"
void server(int readid, int writeid);

int main(int argc, char **argv)
{
    int readid;
    readid = msgget(MQ_KEY1, SVMSG_MODE | IPC_CREAT);
    if(readid < 0)
    {
        perror("open msg failed");
        exit(1);
    }
    else
        printf("mqid: %d\n", readid);

    server(readid, 0);

    return 0;
}

void server(int readid, int writeid)
{
    FILE *fp;
    ssize_t n;
    struct msgmbuf buff;
    char buffer[MSG_MAX];

    buff.mtype = 0;
    n = msgrcv(readid, &buff, MSG_MAX, buff.mtype, 0);
    if(n < 0)
        err_quit("receive msg error");

    buff.mtext[n] = '\0';

    fp = fopen(buff.mtext, "r");
    if(fp == NULL)
    {
        snprintf(buff.mtext + n, sizeof(buff.mtext)-n, ": can't open, %s\n", strerror(errno));
        msgsnd(writeid, &buff, strlen(buff.mtext) + 1, 0);
    }
    else
    {
        char *ptr;
        while((ptr = fgets(buff.mtext, MSG_MAX, fp)) != NULL)
        {
            //msgsnd(writeid, &buff, strlen(buff.mtext) + 1, 0);
            printf(" :%s", buff.mtext);
        }
        fclose(fp);
    }
}
