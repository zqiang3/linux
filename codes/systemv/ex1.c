#include "msg.h"


int main(int arvc, char **argv)
{
    int msqid;
    struct msqid_ds info;
    struct msgmbuf buf;

    msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
    printf("mqid: %d\n", msqid);
    
    buf.mtype = 1;
    buf.mtext[0] = 1;
    msgsnd(msqid, &buf, 1, 0);
    msgctl(msqid, IPC_STAT, &info);
    printf("read-write: %03o, ctytes=%d, qnum = %d, qbutes=%d\n", info.msg_perm.mode & 0777, (int)info.msg_cbytes, (int)info.msg_qnum, (int)info.msg_qbytes);

    system("ipcs -q");
    exit(0);
}
