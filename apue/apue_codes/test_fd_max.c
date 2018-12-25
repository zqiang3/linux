#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    while (1)
    {
        int fd = open("a.txt", O_WRONLY | O_CREAT, 0644);
        if (fd < 0)
        {
            perror("open");
            exit(1);
        }

        printf("fd = %d\n", fd);
    }

    return 0;
}