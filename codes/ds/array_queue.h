#include <stdbool.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct
{
    int front;
    int rear;
    int size;
    int length;
    ElemType *arr;
}Queue;

Queue* MakeQueue(int size);
bool IsQueueEmpty(Queue*);
bool IsQueueFull(Queue*);
bool AppendQueue(Queue*, ElemType);
ElemType PopQueue(Queue*);
int LengthOfQueue(Queue*);
void printQueue(Queue *q);
