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
    char *ptr;
    size_t len;
    unsigned int prio;

    if(argc < 4)
    {
        printf("Usage: sendmq <name> <bytes> <priority>\n");
        exit(1);
    }

    len = atoi(argv[2]);
    prio = atoi(argv[3]);

    mqd = mq_open(argv[1], O_WRONLY);
    if(-1 == mqd)
    {
        perror("open mq failure");
        exit(1);
    }

    ptr = (char *)calloc(len, sizeof(char));
    if (NULL == ptr)
    {
        perror("allocate memory failure");
        mq_close(mqd);
        exit(1);
    }

    rc = mq_send(mqd, ptr, len, prio);
    if(rc < 0)
    {
        perror("write failure");
        mq_close(mqd);
        exit(1);
    }

    free(ptr);
    printf("finished\n");
    printf("pid = %d\n", getpid());
    return 0;
}

