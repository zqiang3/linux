#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

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

    fd = open(filename, O_CREAT|O_RDWR, 0777);
    if(fd < 0)
    {
        printf("error openi\n");
        exit(1);
    }

    p_map = (people*)mmap(NULL, sizeof(people)*10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    temp = 'a';
    for(i=0; i<10; i++)
    {
        printf("name: %s, age: %d\n", (*(p_map+i)).name, (*(p_map+i)).age);
    }
    munmap(p_map, sizeof(people) * 10);

    return 0;
}
