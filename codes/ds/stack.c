#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* genStack(int size)
{
    Stack *st = (Stack *)malloc(sizeof(Stack));
    if(!st)
    {
        perror("malloc Stack");
        return NULL;
    }
    ElemType *arr = (ElemType *)malloc(sizeof(ElemType));
    if(!arr)
    {
        perror("malloc ElemType");
        return NULL;
    }
    st->arr= arr;
    st->size = size;
    st->top = -1;
}

bool isEmpty(Stack *st)
{
    return st->top < 0;
}

bool isFull(Stack *st)
{
    return st->top >= st->size - 1;
}

void push(Stack *st, ElemType value)
{
    if(isFull(st))
        return;

    (st->arr)[++st->top] = value;
}

ElemType topElem(Stack *st)
{
    if(isEmpty(st))
        return 0;

    return (st->arr)[st->top];
}

void printStack(Stack *st)
{
    if(isEmpty(st))
        return;

    int i;
    for(i = 0; i <= st->top; i++)
    {
        printf("%d ", st->arr[i]);
    }
    puts("--------------------------");
}
