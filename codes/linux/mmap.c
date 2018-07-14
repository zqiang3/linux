#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

typedef struct{
    char name[4];
    int age;
}people;

void println(char *text)
{
    printf("%s\n", text);
}

int main(int argc, char **argv)
{
    if(argc < 1)
    {
        printf("Usage %s <filename>\n", argv[0]);
        exit(1);
    }
    int fd, i;
    people *p_map;
    char temp;
    char *filename = argv[1];

    fd = open(filename, O_CREAT|O_RDWR|O_TRUNC, 0777);
    if(fd < 0)
    {
        printf("error open\n");
        exit(1);
    }

    lseek(fd, sizeof(people)*5 - 1, SEEK_SET);
    write(fd, "", 1);
    p_map = (people*)mmap(NULL, sizeof(people)*10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    temp = 'a';
    close(fd);


    struct stat buff;
    stat(filename, &buff);
    printf("filesize: %d\n", buff.st_size);
    for(i=0; i<10; i++)
    {
        temp++;
        memcpy((*(p_map+i)).name, &temp, 2);
        (*(p_map+i)).age = 20 + i;
    }

    printf("initialize over\n");
    sleep(10);
    munmap(p_map, sizeof(people)*10);
    println("umap ok");

}
