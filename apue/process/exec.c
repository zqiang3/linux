#include <unistd.h>


int main(int argc, char **argv)
{
    const char* path = "./hello.py";
    const char *arg1 = "hello.py";
    const char *arg2 = "arg2";
    const char *arg3 = "arg3";
    execl(path, arg1, arg2, arg3, (char *)0);
}
