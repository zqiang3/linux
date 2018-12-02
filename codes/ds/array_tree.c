#include <stdio.h>
#include <stdlib.h>
#include "array_tree.h"


void append_tree(Tree* tree, ElemType value)
// 排序二叉树，增加节点
{
    int cur = 1;
    ElemType *arr = tree->arr;
    while(cur < tree->size && arr[cur] != 0)
    {
        if(value < arr[cur])
            cur = 2 * cur;
        else
            cur = 2 * cur + 1;
    }
    if(cur < tree->size)
        arr[cur] = value;
    else
        puts("not enough space");
}



static void _tranverse_tree(Tree* tree, int root)
{
    if(root > tree->size)
        return;

    if((tree->arr)[root] == 0)
        return;

    printf("%d ", (tree->arr)[root]);
    if(root * 2 < tree->size)
        _tranverse_tree(tree, root*2);
    if(root * 2 + 1 < tree->size)
        _tranverse_tree(tree, root*2 + 1);
}

void tranverse_tree(Tree *tree)
{
    _tranverse_tree(tree, 1);
}

Tree* genTree(int size)
{
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    if(!tree)
    {
        perror("malloc");
        return NULL;
    }
    ElemType *arr = (ElemType *)malloc(size * sizeof(ElemType));
    if(!arr)
    {
        perror("malloc");
        return NULL;
    }
    
    tree->arr = arr;
    tree->size = size;
    return tree;
}
