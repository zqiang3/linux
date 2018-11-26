#include <stdio.h>
#include "cutil.h"

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        puts("Usage: ./cadd <num_a> <num_b>");
        exit(1);
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    char temp[1024];
    printf("a + b = %d\n", a + b);
    itobs(a + b, temp);
    showbnum(temp);

    return 0;
}
