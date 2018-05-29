#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>

int main(void)
{
    key_t key;
    int proj_id = 0;
    char *pathname = "./program";

    proj_id = 1;

    key = ftok(pathname, proj_id);
    if(key == -1)
    {
        perror("Cannot generate the IPC key\n");
        return (1);
    }

    printf("proj_id = %d pathname = %s IPC key = %d\n", proj_id, pathname, key);

    proj_id = 2;
    key = ftok(pathname, proj_id);
    if (key == -1)
    {
        perror("Cannot generate the IPC key\n");
        return (1);
    }

    printf("proj_id = %d pathname = %s IPC key = %d\n", proj_id, pathname, key);
    return (0);

}
