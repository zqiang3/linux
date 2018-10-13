#include <stdio.h>

int GetNumber(int *arr, int row, int col, int number);

int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
const int col_size = 4;
const int row_size = sizeof(matrix) / (4 * 4);


int main(int argc, char ** argv)
{
    int i, j;
    for(i = 0; i < row_size; i ++)
    {
        for(j = 0; j < col_size; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("rows=%d, cols=%d\n", row_size, col_size);
    int find_value = atoi(argv[1]);
    printf("find_value=%d\n", find_value);
    int found = GetNumber((int*)matrix, row_size, col_size, find_value);
    printf("found=%d\n", found);

}


int GetNumber(int *arr, int rows, int cols, int number)
{
    if(!arr)
        return 0;

    int row = 0;
    int col = cols -1;

    int found = 0;

    while(row < row_size && col >= 0)
    {
        int test_value = *(arr + row * col_size + col);
        if(test_value == number)
        {
            printf("row=%d, col=%d\n", row, col);
            found = 1;
            break;
        }
        else if(test_value > number)
            col--;
        else
            row++;
    }

    return found;
}
