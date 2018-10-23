#include <stdio.h>

typedef int ElemType;
void swap(ElemType *arr, int i,  int j);
void select_sort(ElemType *arr, int size);
void printArray(ElemType *arr, int size);

int main(int argc, char **argv)
{
    ElemType arr[] = 
    {
        1, 3, 9, 7, 5, 21, 19
    };
    int size = sizeof(arr) / sizeof(ElemType);
    select_sort(arr, size);
    printArray(arr, size);
}

void select_sort(ElemType *arr, int size)
{
    int i, j;
    int min;
    for(i = 0; i < size -1; i++)
    {
        min = i;
        for(j = i + 1 ; j < size; j++)
        {
            if(arr[j] < arr[min])
            {
                min = j;
            }
        }
        swap(arr, i, min);
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
