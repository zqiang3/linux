#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>

void println(const char *s)
{
    puts(s);
}


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Usage cmd <length>\n");
        exit(1);
    }

    int len = atoi(argv[1]);
    println("try init ArrayList");
    ArrayList *L = MakeArrayList();
    if(!L)
    {
        println("MakeArrayList failed!");
        exit(1);
    }

    // L = NULL;
    // len = 0;
    bool flag;
    flag = InitList(L, len);
    if(!flag)
    {
        println("InitList failed!");
        exit(1);
    }

    println("append 0");
    AppendList(L, 0);
    printListLength(L);

    println("append 1");
    AppendList(L, 1);
    printListLength(L);
    
    println("append 2");
    AppendList(L, 2);
    printListLength(L);

    println("pop");
    ElemType value = PopList(L);
    printListLength(L);

    println("pop");
    value = PopList(L);
    printListLength(L);

    println("insert index: 0, value: 10");
    InsertList(L, 0, 10);
    printListLength(L);

    println("insert index: 1, value: 11");
    InsertList(L, 1, 11);
    printListLength(L);

    println("insert index: 1, value: 12");
    InsertList(L, 1, 12);
    printListLength(L);


    return 0;
}

