#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef int ElemType;
typedef struct
{
    ElemType *arr;
    int size;
}Heap;

Heap* initHeap();
void appendHeap(Heap *heap, ElemType value);
void appendValues(Heap *heap, ElemType *arr, int sum);
void traverseHeap(Heap *heap);
void _traverse(ElemType *arr, int i);

int main(int argc, char **argv)
{
    Heap *heap = initHeap();
    int arr[] = 
    {
       4, 9, 17, 12, 19, 20, 60, 65, 30, 50 
    };
    appendValues(heap, arr, sizeof(arr) / sizeof(ElemType));
    traverseHeap(heap);
    

    printf("hello\n");
    return 0;
}


Heap* initHeap()
{
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->arr = (ElemType*)malloc(sizeof(ElemType)*MAX);
    int i;
    for(i = 0; i < MAX; i++)
        heap->arr[i] = 0;

    return heap;
}

void appendHeap(Heap *heap, ElemType value)
{
    if((heap->size) >= (MAX - 1))
        return;

    heap->size++;
    heap->arr[heap->size] = value;
}

void appendValues(Heap *heap, ElemType *arr, int sum)
{
    int i;
    for(i = 0; i < sum; i++)
        appendHeap(heap, arr[i]);
}


void traverseHeap(Heap *heap)
{
    if(!(heap->arr))
        return;

    int i = 1;
    _traverse(heap->arr, i);
}


void _traverse(ElemType *arr, int i)
{
    if(arr[i] == 0 || i >= MAX)
        return;

    _traverse(arr, i * 2);
    printf("%d\n", arr[i]);
    _traverse(arr, i * 2 + 1);
}
