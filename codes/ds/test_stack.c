#include <stdio.h>
#include "stack.h"

int main(int argc, char *argv)
{
    Stack *ss = genStack(100);
    push(ss, 1);
    push(ss, 3);
    push(ss, 7);
    printf("ele = %d\n", topElem(ss));
    printStack(ss);
    
}
