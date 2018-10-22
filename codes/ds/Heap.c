#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef int ElemType;
typedef struct
{
    ElemType *arr;
    int size;
}Heap;

void swap(ElemType *arr, int i, int j);
Heap* initHeap();
void appendHeap(Heap *heap, ElemType value);
void appendValues(Heap *heap, ElemType *arr, int sum);
void traverseHeap(Heap *heap);
void _traverse(ElemType *arr, int i);
void insertHeap(Heap* heap, ElemType value);

int main(int argc, char **argv)
{
    Heap *heap = initHeap();
    int arr[] = 
    {
       4, 9, 17, 12, 19, 20, 60, 65, 30, 50 
    };
    appendValues(heap, arr, sizeof(arr) / sizeof(ElemType));
    traverseHeap(heap);

    insertHeap(heap, 2);
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

void insertHeap(Heap* heap, ElemType value)
{
    appendHeap(heap, value);
    int child = heap->size;
    ElemType *arr = heap->arr;
    int parent = child / 2;
    while(parent > 0)
    {
        if(arr[child] < arr[parent])
            swap(arr, child, parent);
        child = parent;
        parent = child / 2;
    }
}


void swap(ElemType *arr, int i, int j)
{
    ElemType temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
