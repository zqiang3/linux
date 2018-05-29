#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MQ_NAME ("/tmp")
#define MQ_FLAG (O_RDWR | O_CREAT | O_EXCL)
#define FILE_MODE (S_IRUSR | S_IRGRP | S_IROTH) 

void create_mq(void);
void unlink_mq(void);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("args less than 2!\n");
        exit(1);
    }

    char *cmd = argv[1];
    if (strcmp(cmd, "create") == 0)
        create_mq();
    else if (strcmp(cmd, "unlink") == 0)
        unlink_mq();
    else
        return 0;

    return 0;
}

void create_mq(void)
{
    mqd_t posixmq;
    int rc = 0;
    struct mq_attr mqattr;
    mqattr.mq_maxmsg = 3;
    mqattr.mq_msgsize = 2048;

    posixmq = mq_open(MQ_NAME, MQ_FLAG, FILE_MODE, &mqattr);
    if(-1 == posixmq)
    {
        perror("create mq failure");
        exit(1);
    }

    mqattr.mq_flags = 0;
    mq_setattr(posixmq, &mqattr, NULL);

    rc = mq_getattr(posixmq, &mqattr);
    if (-1 == rc)
    {
        perror("get mq attr failure");
        exit(1);
    }

    printf("block flag: %ld\n", mqattr.mq_flags);
    printf("max msgs: %ld\n", mqattr.mq_maxmsg);
    printf("max bytes: %ld\n", mqattr.mq_msgsize);
    printf("cur msg: %ld\n", mqattr.mq_curmsgs);
}

void unlink_mq(void)
{
    int rc = 0;
    rc = mq_unlink(MQ_NAME);
    if(0 != rc)
    {
        perror("delete failure");
        exit(1);
    }
}
