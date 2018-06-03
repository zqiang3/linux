#include "strlen.h"
#include <stdio.h>

int main(void)
{
    int n;
    char *p = "hello, mama";
    n = strlen_v1(p);
    printf("len: %d\n", n);
    return 0;
}
