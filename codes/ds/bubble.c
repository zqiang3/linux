#include <stdio.h>

typedef int ElemType;
void swap(ElemType *arr, int i,  int j);
void bubble(ElemType *arr, int size);
void printArray(ElemType *arr, int size);

int main(int argc, char **argv)
{
    ElemType arr[] = 
    {
        1, 3, 9, 7, 5, 21, 19
    };
    int size = sizeof(arr) / sizeof(ElemType);
    bubble(arr, size);
    printArray(arr, size);
}

void bubble(ElemType *arr, int size)
{
    int i, j;
    int flag;
    for(i = 0; i < size -1; i++)
    {
        flag = 1;
        for(j = size -2 ; j >= i; j--)
        {
            if(arr[j+1] < arr[j])
            {
                swap(arr, j+1, j);
                flag = 0;
            }
        }

        if(flag)  // no swap
            break;
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
