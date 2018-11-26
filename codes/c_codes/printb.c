#include "cutil.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        puts("Usage: ./printb <num>");
        exit(1);
    }

    int a = atoi(argv[1]);
    char buf[1024];

    itobs(a, buf);
    showbnum(buf);

    return 0;
}
