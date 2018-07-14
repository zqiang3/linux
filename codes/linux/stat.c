#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *f = argv[1];
    struct stat buff;
    stat(f, &buff);
    printf("filename: %s\n", f);
    printf("file size=%d\n", buff.st_size);
    printf("file uid=%d\n", buff.st_uid);
    return 0;
}
