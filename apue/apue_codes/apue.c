#include <stdlib.h>

void err_sys(const char* msg)
{
    perror(msg);
    exit(1);
}
