#include <stdbool.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct node
{
    ElemType value;
    struct node * next;
}Node;

typedef struct
{
    Node *front;
    Node *rear;
    int size;
}Queue;

Queue* MakeQueue();
bool IsQueueEmpty(Queue*);
bool IsQueueFull(Queue*);
bool AppendQueue(Queue*, ElemType);
ElemType PopQueue(Queue*);
int LengthOfQueue(Queue*);
void printQueue(Queue *q);
