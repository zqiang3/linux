#include "cutil.h"

char * itobs(int n, char *ps)
{
    int i;
    static int size = 8 * sizeof(int);
    for(i = size - 1; i >= 0; i--, n >>= 1)
        ps[i] = (01 & n) + '0';

    ps[size] = '\0';
    return ps;
}

void showbnum(char *ps)
{
    int count = 1;
    while(*ps != '\0')
    {
        printf("%c", *ps++);
        if(count++ % 4 == 0)
            printf(" ");
        
    }
    puts("");
}

