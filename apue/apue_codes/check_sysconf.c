#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("_SC_OPEN_MAX: %ld\n", sysconf(_SC_OPEN_MAX));
}