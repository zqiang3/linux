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

