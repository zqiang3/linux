#include <stdio.h>

typedef int ElemType;
void swap(ElemType *arr, int i,  int j);
void mergeSort(ElemType *arr, int left, int right);
void merge(ElemType* arr, int left, int middle, int right);
void printArray(ElemType *arr, int size);

int main(int argc, char **argv)
{
    ElemType arr[] = 
    {
        1, 3, 9, 7, 5, 21, 19
    };
    int size = sizeof(arr) / sizeof(ElemType);
    mergeSort(arr, 0, size-1);
    printArray(arr, size);
}

void mergeSort(ElemType *arr, int left, int right)
{
    if(left >= right)
        return;

    int middle = (right+left) / 2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle+1, right);
    merge(arr, left, middle, right);
}

void merge(ElemType* arr, int left, int middle, int right)
{
    ElemType temp[right-left+1];
    int i, j, k;
    k = 0;
    for(i=left,j=middle+1;i<=middle && j<=right; k++)
    {
        if(arr[i] < arr[j])
            temp[k] = arr[i++];
        else
            temp[k] = arr[j++];
    }
    while(i <= middle)
    {
        temp[k++] = arr[i++];
    }

    while(j<=right)
        temp[k++] = arr[j++];

    for(i = left, k = 0; i <= right; )
        arr[i++] = temp[k++];
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
