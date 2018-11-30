#include "linklist.h"
#include <stdio.h>
#include <string.h>

int comp_item(void *a, void *b)
{
    Item *m = (Item *)a;
    Item *n = (Item *)b;
    int ret;
    if( (ret = strcmp(m->name, n->name)) != 0)
        return ret;

    else
        return m->age - n->age;
}

void print_item(void *a)
{
    Item *m = (Item *)a;
    printf("name=%-20s age=%d\n", m->name, m->age);
}

int main(int argc, char *argv[])
{
    List *list = GenAndInitList();
    Item i = 
    {
        "zhuwei",
        29
    };

    OrderedInsert(list, i, comp_item);

    Item item1 = 
    {
        "liuchen",
        29
    };
    OrderedInsert(list, item1, comp_item);


    Item item2 = 
    {
        "zq",
        30
    };
    OrderedInsert(list, item2, comp_item);
    printList(list, print_item);
    printf("%p\n", list);

    return 0;
}
