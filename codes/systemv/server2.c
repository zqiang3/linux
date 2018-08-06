#include "msg.h"
void server(int readid, int writeid);

int main(int argc, char **argv)
{
    int mqid;
    mqid = msgget(MQ_KEY1, SVMSG_MODE | IPC_CREAT);
    if(mqid< 0)
    {
        perror("open msg failed");
        exit(1);
    }
    else
        printf("mqid: %d\n", mqid);

    server(mqid, mqid);

    return 0;
}

void server(int readid, int writeid)
{
    println("enter server");
    FILE *fp;
    ssize_t n;
    struct mymesg mesg;
    char *ptr;
    pid_t pid;

    signal(SIGCHLD, sig_child);

    // read pathname from IPC
    for(;;)
    {
        println("wait for client...");
        mesg.mesg_type = 1;
        n = mesg_recv(readid, &mesg);
        if(n <= 0)
        {
            perror("read pathname failed");
            continue;
        }
        else
            println("read pathname success");

        mesg.mesg_data[n] = '\0';

        ptr = strchr(mesg.mesg_data, ' ');
        if(ptr == NULL)
        {
            printf("bogus request: %s\n", mesg.mesg_data) ;
            continue;
        }

        *ptr++ = 0;
        writeid = atoi(mesg.mesg_data);
        printf("get mesg: writeid=%d, path=%s\n", writeid, ptr);

        pid = fork();
        if(pid == 0)
        {
            printf("child process is %d\n", getpid());
            
            fp = fopen(ptr, "r");
            if(fp == NULL)
            {
                snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data)-n, ": can't open, %s\n", strerror(errno));
                mesg.mesg_len = strlen(ptr);
                memmove(mesg.mesg_data, ptr, mesg.mesg_len);
                mesg_send(writeid, &mesg);
            }
            else
            {
                while(fgets(mesg.mesg_data, MSG_MAX, fp) != NULL)
                {
                    mesg.mesg_len = strlen(mesg.mesg_data);
                    mesg_send(writeid, &mesg);
                }
                fclose(fp);
            }
            mesg.mesg_len = 0;
            mesg_send(writeid, &mesg);
            exit(0);
        }
    }
}
