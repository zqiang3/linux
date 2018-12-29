#include <stdio.h>
#include <stdlib.h>


void myexit1();
void myexit2();
void myexit3(int n);
void err_sys(const char *s);
void err_perror(const char *s);

int main(void)
{
    int ret;
    ret = atexit(myexit1);
    if(ret != 0)
        err_perror("atexit");

    ret = atexit(myexit2);
    if(ret != 0)
        err_perror("atexit");

    //? ret = atexit(myexit3);

    puts("hello, stranger");
    return 0;
    
}

void myexit1()
{
    puts("myexit1");
}

void myexit2()
{
    puts("myexit2");
}

void myexit3(int n)
{
    puts("myexit3");
}

void err_sys(const char *s)
{
    puts(s);
    exit(1);
}

void err_perror(const char *s)
{
    perror(s);
    exit(1);
}
