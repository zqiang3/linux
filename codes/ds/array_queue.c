#include "array_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Queue* MakeQueue(int size)
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if(!q)
    {
        perror("malloc");
        return NULL;
    }

    ElemType *arr = (ElemType*)malloc(size * sizeof(Queue));
    if(!q)
    {
        perror("malloc");
        return NULL;
    }


    q->front = 0;
    q->rear = size - 1;
    q->size = size;
    q->length= 0;
    q->arr = arr;
    return q;
}

bool IsQueueEmpty(Queue *q)
{
    if(!q)
    {
        puts("Queue is NULL!");
        return false;
    }

    return q->length == 0;
}

bool IsQueueFull(Queue *q)
{
    if(!q)
    {
        puts("Queue is NULL!");
        return false;
    }

    return q->length >= q->size;
}

int LengthOfQueue(Queue *q)
{
    if(!q)
    {
        puts("Queue is NULL!");
        return 0;
    }

    return q->length;
}

bool AppendQueue(Queue *q, ElemType value)
{
    if(!q)
    {
        puts("Queue is NULL!");
        return false;
    }
    if(IsQueueFull(q))
    {
        puts("Queue is full!");
        return false;
    }

    q->rear = ++q->rear % q->size;
    q->arr[q->rear] = value;
    q->length++;
}

ElemType PopQueue(Queue *q)
{
    assert(q != NULL);
    assert(!IsQueueEmpty(q));


    q->front = ++q->front % q->size;
    q->length--;
}

void printQueue(Queue *q)
{
    if(!q)
        return;

    if(IsQueueEmpty(q))
        return;

    int i;
    for(i = 0; i < q->length; i++)
    {
        printf("%d ", q->arr[(i + q->front) % q->size]);
    }

    printf("--------------------------------\n\n");
}
