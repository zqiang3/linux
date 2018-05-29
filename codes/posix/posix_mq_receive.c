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

int main(int argc, char *argv[])
{
    mqd_t mqd;
    int rc = 0;
    int n = 0;
    char *ptr;
    size_t len;
    unsigned int prio;
    struct mq_attr attr;

    if(argc < 2)
    {
        printf("Usage: readmq <name>\n");
        exit(1);
    }

    mqd = mq_open(argv[1], O_RDONLY);
    if(-1 == mqd)
    {
        perror("open mq failure");
        exit(1);
    }

    rc = mq_getattr(mqd, &attr);
    if (rc < 0)
    {
        perror("receive msg failure");
        exit(1);
    }
    printf("number of msgs = %d\n", attr.mq_curmsgs);

    ptr = (char *)calloc(attr.mq_msgsize, sizeof(char));
    if (NULL == ptr)
    {
        perror("allocate memory failure");
        mq_close(mqd);
        exit(1);
    }

    n = mq_receive(mqd, ptr, attr.mq_msgsize, &prio);
    if(n < 0)
    {
        perror("read failure");
        mq_close(mqd);
        free(ptr);
        exit(1);
    }

    printf("read %ld bytes\npriority is %u\n", (long)n, prio);
    return 0;
}

