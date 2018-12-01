#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>

void println(const char *s)
{
    puts(s);
}

void eatline()
{
    while(getchar() != '\n')
        continue;
}


int main(int argc, char** argv)
{

    println("try init Queue");
    Queue *q = MakeQueue(5);
    if(!q)
    {
        puts("MakeQueue failed");
        exit(1);
    }
    
    char c;
    ElemType value;
    puts("input command(a: add element, d: delete element, q: quit)");
    while( (c = getchar()) != 'q')
    {
        if(c != 'a' && c != 'd')
        {
            puts("invalid command");
        }
        else if(c == 'a')
        {
            eatline();
            puts("input a number");
            scanf("%d", &value);
            AppendQueue(q, value);
            printQueue(q);
        }
        else if(c == 'd')
        {
            PopQueue(q);
            printQueue(q);
        }

        eatline();
        puts("input command(a: add element, d: delete element, q: quit)");
    }
}
