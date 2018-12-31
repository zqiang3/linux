#include <stdio.h>
#include <stdlib.h>
#include "apue.h"
#include <sys/types.h>
static void output_char(const char *str);

int main()
{
    pid_t pid;
    if ( (pid = fork()) < 0)
        err_sys("fork");
    else if (pid == 0)
    {
        output_char("output from child\n");
        
    }
    else
    {
        output_char("output from parent\n");
        
    }

    exit(0);
        
    
}

static void
output_char(const char *str)
{
    int c;

    setbuf(stdout, NULL);
    for( ; (c = *str++) != 0; )
    {
        sleep(1);
        putc(c, stdout);
        
    }

}
