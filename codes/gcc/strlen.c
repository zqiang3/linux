#include "strlen.h"

int strlen_v1(const char *p)
{
    int i = 0;
    while(p[i])
        i++;
    return i;
}

int strlen_v2(const char *p)
{
    int i = 0;
    char c;
    while(1)
    {
        c = p[i];
        if (c == '\0')
            break;
        else
            i++;
    }

    return i;
}
