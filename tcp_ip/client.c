#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "apue.h"

int main(void)
{
    struct sockaddr_in peer;
    int s;
    int rc;
    char buf[1];

    peer.sin_family = AF_INET;
    peer.sin_port = htons(7500);
    peer.sin_addr.s_addr = inet_addr("127.0.0.1");
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
        err_sys("socket");

    rc = connect(s, (struct sockaddr*)&peer, sizeof(peer));
    if (rc != 0)
        err_sys("connect");

    rc = send(s, "1", 1, 0);
    if (rc <= 0)
        err_sys("call failed");
    else
        printf("%c\n", buf[0]);

    exit(0);
}


