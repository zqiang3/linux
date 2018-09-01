#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define ONE_MB (1024 * 1024)

int main(int argc, char **argv)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    long pages = sysconf(_SC_PHYS_PAGES);
    printf("the number of processors: %ld\n", sysconf(_SC_NPROCESSORS_CONF));
    printf("the number of processors available: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
    printf("the pagesize: %ld\n", pagesize); 
    printf("the number of pages: %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("the number of available pages: %ld\n", sysconf(_SC_AVPHYS_PAGES));
    printf("the memory size: %lld MB\n", (long long)pagesize * (long long)pages / ONE_MB);
    printf("the number of file max opened: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("the number of ticks per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("the max length of host name: %ld\n", sysconf(_SC_HOST_NAME_MAX));
    printf("the max length of login name: %ld\n", sysconf(_SC_LOGIN_NAME_MAX));
    return 0;
}
