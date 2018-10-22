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
int randint();
Heap* randomTest(int num);

Heap* initHeap();
void insertHeap(Heap* heap, ElemType value);
void traverseHeap(Heap *heap);
void _traverse(ElemType *arr, int i);
void insertHeap(Heap* heap, ElemType value);
void deleteMin(Heap* heap);
void printHeap(Heap* heap);

int main(int argc, char **argv)
{
    Heap *heap = initHeap();
    insertHeap(heap, 13);
    insertHeap(heap, 14);
    insertHeap(heap, 16);
    insertHeap(heap, 19);
    insertHeap(heap, 21);
    insertHeap(heap, 19);
    insertHeap(heap, 68);
    insertHeap(heap, 65);
    insertHeap(heap, 26);
    insertHeap(heap, 32);
    insertHeap(heap, 22);
    printHeap(heap);

    deleteMin(heap);
    printHeap(heap);
    
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
    int child, parent;
    ElemType *arr = heap->arr;

    for(child = heap->size + 1; ; )
    {
        parent = child / 2;
        if(parent <= 0 || arr[parent] <= value )
            break;

        arr[child] = arr[parent];
        child = parent;
    }

    arr[child] = value;
    heap->size++;
}

void deleteMin(Heap* heap)
{
    int size = heap->size;
    if(size <= 0)
        return;

    int parent;
    ElemType *arr = heap->arr;
    int child;
    ElemType last = arr[heap->size];
    for(parent = 1; ;)
    {
        child = parent * 2;
        if(child > size)
            break;

        
        if(child < size && arr[child + 1] < arr[child])
            child++;

        if(last < arr[child])
            break;
        else
        {
            arr[parent] = arr[child];
            parent = child;
            
        }

    }
    arr[parent] = last;
    heap->size--;

    return;
}


void swap(ElemType *arr, int i, int j)
{
    ElemType temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void printHeap(Heap* heap)
{
    int i;
    for(i = 0; i <= heap->size; i++)
        printf("%d ", heap->arr[i]);

    printf("\n");
}


Heap* randomTest(int num)
{
    Heap *heap = initHeap();

    int i, ranv;
    for(i = 0; i < num; i++)
    {
        ranv = randint();
        printf("insert %d\n", ranv);
        insertHeap(heap, ranv);
        
    }

    printHeap(heap);
    return heap;
    
}

int randint()
{
    return rand() % 100 + 1;
}

