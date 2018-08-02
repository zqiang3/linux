#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>

int main(int arvc, char **argv)
{
    int msqid;
    struct msqid_ds info;
    struct msgbuf buf;

    msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREATE);
    
    buf.mtype = 1;
    buf.mtext[0] = 1;
    msgsnd(msqid, &buf, 1, 0);
    msgctl(msqid, IPC_STAT, &Info);
    printf("read-write: %03o, ctytes=%lu, qnum = %lu, qbutes=%lu\n", info.msg_perm.mode & 0777, (ulong_t)info.msg_cbytes, (ulong_t)info.msg_qnum, (ulong_t)info.msg_qbytes);

    system("ipcs -q");
    msgctl(msqid, IPC_RMID, null);
    exit(0);
}
