#include <stdio.h>
#include <stdlib.h>
#include "rand.h"

#define MAX 1000
typedef int ElemType;
void swap(ElemType *arr, int i,  int j);
void insertSort(ElemType *arr, int size, int inc);
void hillSort(ElemType *arr, int size);
void printArray(ElemType *arr, int size);
ElemType* initRandom();

int main(int argc, char **argv)
{
    ElemType* arr = initRandom();
    int size = MAX;
    printf("size=%d\n", size);
    hillSort(arr, size);
    printArray(arr, size);
}

void hillSort(ElemType *arr, int size)
{
    if(size <= 1)
        return;

    int inc = size / 2;
    while(inc >= 1)
    {
        insertSort(arr, size, inc);
        inc /= 2;
    }
}

void insertSort(ElemType *arr, int size, int inc)
{
    int i, j;
    int temp;
    for(i = 1; i < size; i++)
    {
        if(i - inc < 0)
            continue;
        if(arr[i] > arr[i-inc])
            continue;

        temp = arr[i];
        for(j = i; j - inc >= 0; j -= inc)
        {
            if(temp > arr[j - inc])
                break;

            arr[j] = arr[j - inc];

        }
        if(j != i)
            arr[j] = temp;
    }
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


ElemType* initRandom()
{
    ElemType *arr = (ElemType *)malloc(sizeof(ElemType) * MAX);
    int i;
    for(i = 0; i < MAX; i++)
        arr[i] = randint(1000);
    return arr;

}
