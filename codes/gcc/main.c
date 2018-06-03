#include "strlen.h"
#include <stdio.h>

int main(void)
{
    int n;
    char *p = "hello, mama";
    n = strlen_v1(p);
    printf("len: %d\n", n);
    printf("len: %d\n", strlen_v2(p));
    return 0;
}
