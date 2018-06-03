#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

void del_newline(char *);

int main(void)
{
    char buff[MAX];
    char command[MAX];
    FILE *fp;
    int ret;
    char *ptr;

    printf("prompt: imput filename\n");
    ptr = fgets(buff, MAX, stdin);
    if(ptr < 0)
    {
        perror("fgets error\n");
        exit(1);
    }

    del_newline(buff);
    printf("filename is: %s\n", buff);

    snprintf(command, sizeof(command), "cat %s", buff);
    printf("command is: %s\n", command);
    

    fp = popen(command, "r");
    int count = 0;
    while(fgets(buff, MAX, fp) != NULL)
    {
        fputs(buff, stdout);
        count++;
        printf("count: %d\n", count);
    }

    pclose(fp);
    return 0;
}

void del_newline(char *p)
{
    int n;
    n = strlen(p);
    if(p[n-1] == '\n')
        p[n-1] = '\0';
}
