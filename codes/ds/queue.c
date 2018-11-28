#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Queue* MakeQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if(!q)
    {
        perror("malloc");
        return q;
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

bool IsQueueEmpty(Queue *q)
{
    if(!q)
    {
        puts("Queue is NULL!");
        return false;
    }

    return q->size == 0;
}

bool IsQueueFull(Queue *q)
{
    if(!q)
    {
        puts("Queue is NULL!");
        return false;
    }

    return q->size == MAXSIZE;
}

int LengthOfQueue(Queue *q)
{
    if(!q)
    {
        puts("Queue is NULL!");
        return 0;
    }

    return q->size;
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

    Node *newnode = (Node*)malloc(sizeof(Node));
    if(!newnode)
    {
        perror("malloc");
        return false;
    }

    newnode->value = value;
    newnode->next = NULL; 

    if(!q->front)
    {
        q->front = newnode;
    }
    else
    {
        q->rear->next = newnode;
    }
    q->rear = newnode;

    q->size++;
}

ElemType PopQueue(Queue *q)
{
    assert(q != NULL);
    assert(!IsQueueEmpty(q));

    Node *node = q->front;
    ElemType value = node->value;
    q->front =q->front->next;
    q->size--;
    if(IsQueueEmpty(q))
        q->rear = NULL;

    free(node);
}

void printQueue(Queue *q)
{
    if(!q)
        return;

    if(!q->front)
        return;

    Node *cur = q->front;
    int count = 0;
    puts("print Queue:");
    while(cur)
    {
        printf("Q[%d] = %d\n", count++, cur->value);
        cur = cur->next;
    }
    printf("--------------------------------\n\n");
}
