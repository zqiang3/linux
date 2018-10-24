#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct
{
    ElemType *arr;
    int size;
}Heap;

void swap(ElemType *arr, int i,  int j);
void heapSort(ElemType *arr, int size);
void printArray(ElemType *arr, int size);
void insertHeap(Heap* heap, ElemType value);
ElemType getMin(Heap *heap);


int main(int argc, char **argv)
{
    ElemType arr[] = 
    {
        1, 3, 5,  2, 19, 9, 7, 17, 21, 12
    };
    int size = sizeof(arr) / sizeof(ElemType);

    heapSort(arr, size);
    
}

void heapSort(ElemType *arr, int size)
{

    int i, j;
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->arr = (ElemType*)malloc(sizeof(ElemType) * 1000);
    heap->size = 0;
    for(i = 0; i < size; i++)
    {
        insertHeap(heap, arr[i]);
    }
    printArray(heap->arr, heap->size + 1);

    int value;
    for(i = 0; i < size; i++)
    {
        value = getMin(heap);
        printf("%d ", value);

    }


    printf("\n");
}

void printArray(ElemType *arr, int size)
{
    int i;
    for(i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}


void swap(ElemType *arr, int i,  int j)
{
    ElemType temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void insertHeap(Heap* heap, ElemType value)
{
    ElemType *arr = heap->arr;
    heap->size++;
    int i, parent;
    i = heap->size;
    while(i >= 2)
    {
        if(value >= arr[i / 2])
            break;

        arr[i] = arr[i / 2];
        i /= 2;
    }
    arr[i] = value;
}

ElemType getMin(Heap *heap)
{
    if(heap->size <= 0)
        return 0;

    ElemType *arr = heap->arr; 
    ElemType min = arr[1];

    ElemType value = arr[heap->size];
    int i = 1;
    int child;
    while(2*i <= heap->size)
    {
        child = 2 * i;
        if(2*i+1<=heap->size && arr[2*i+1] < arr[2*i])
            child ++;
        if(value < arr[child])
            break;

        arr[i] = arr[child];
        i = child;
    }
    arr[i] = value;

    heap->size--;
    return min;
}
