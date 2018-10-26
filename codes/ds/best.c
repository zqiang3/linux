#include <stdio.h>

int get_depth(int i);
int get_best(int *arr, int i, int size);

int main(int argc, char** argv)
{
    int arr[] = 
    {
        0, 7, 2, 9

    };
    int size = 3;
    int best = get_best(arr, 1, size);

    printf("best=%d\n", best);

}

int get_best(int *arr, int i, int size)
{
    int depth = get_depth(i);
    if(i+depth>size)
        return arr[i];

    int left, right;
    int best;
    left = get_best(arr, i+depth, size);
    right = get_best(arr, i+depth+1, size);
    best = left>right ? left: right;
    return arr[i] + best;

}


int get_depth(int i)
{

    int sum, n;
    n = 1;
    sum = (n + 1) * n / 2;
    while(i > sum)
    {
        n ++;
        sum = (n + 1) * n / 2;
    }

    return n;
}
