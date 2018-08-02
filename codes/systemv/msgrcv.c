#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/ipc.h>
#include <linux/msg.h>

void err_quit(const char*);
void println(char *ptr)
{
    printf("%s\n", ptr);
}

int main(int argc, char **argv)
{
    if(argc < 4)
    {
        printf("arc less than 4");
        exit(1);
        
    }
    else

    {
        struct msgbuf *buff;
        char *path = argv[1];
        int len = atoi(argv[2]);
        int type = atoi(argv[3]);
        key_t key = ftok(path, 1);
        int open_mode = 0666 | IPC_CREAT;
        int mqid = msgget(key, open_mode);

        buff = malloc(MSGMAX);
        int flag = 0;
        int n = msgrcv(mqid, buff, MSGMAX, type, flag);
        printf("read %d bytes, type=%ld\n", n, buff->mtype);
        return 0;
        
    }


}


void err_quit(const char *info)
{
    printf("%s\n", info);
    exit(1);
}
