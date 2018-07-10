#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    int ret;
    int perms = S_IRUSR | S_IRGRP | S_IROTH | S_IXOTH;
    ret = chmod(argv[1], perms);
    if(ret < 0)
    {
        perror("Cannot modify the permission of the file");
        exit(1);
    }

    return 0;
}
