#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef int ElemType;
typedef struct
{
    ElemType *arr;
    int size;
}Tree;

Tree* initTree();
void appendTree(Tree *tree, ElemType value);
void appendValues(Tree *tree, ElemType *arr, int sum);
void traverseTree(Tree *tree);
void _traverse(ElemType *arr, int i);

int main(int argc, char **argv)
{
    Tree *tree = initTree();
    int arr[] = 
    {
       4, 9, 17, 12, 19, 20, 60, 65, 30, 50 
    };
    appendValues(tree, arr, sizeof(arr) / sizeof(ElemType));
    traverseTree(tree);
    

    printf("hello\n");
    return 0;
}


Tree* initTree()
{
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    tree->size = 0;
    tree->arr = (ElemType*)malloc(sizeof(ElemType)*MAX);
    int i;
    for(i = 0; i < MAX; i++)
        tree->arr[i] = 0;

    return tree;
}

void appendTree(Tree *tree, ElemType value)
{
    if((tree->size) >= (MAX - 1))
        return;

    tree->size++;
    tree->arr[tree->size] = value;
}

void appendValues(Tree *tree, ElemType *arr, int sum)
{
    int i;
    for(i = 0; i < sum; i++)
        appendTree(tree, arr[i]);
}


void traverseTree(Tree *tree)
{
    if(!(tree->arr))
        return;

    int i = 1;
    _traverse(tree->arr, i);
}


void _traverse(ElemType *arr, int i)
{
    if(arr[i] == 0 || i >= MAX)
        return;

    _traverse(arr, i * 2);
    printf("%d\n", arr[i]);
    _traverse(arr, i * 2 + 1);
}
