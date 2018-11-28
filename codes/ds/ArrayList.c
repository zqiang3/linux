#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>


ArrayList* MakeArrayList(void)
{
    ArrayList *L = (ArrayList*)malloc(sizeof(ArrayList));
    return L;
}


// 初始化
void InitList(ArrayList *L, int size)
{
    L->head = (ElemType *)malloc(size * sizeof(ElemType));
    L->size= size;
    L->length= 0;
}

// 末尾添加
void AppendList(ArrayList* L, ElemType value)
{
    if(IsListFull(L))
    {
        puts("warning: excess max size");
        return;
    }

    *(L->head + L->length) = value;
    L->length ++;

}

bool IsListFull(ArrayList *L)
{
    if(L->length >= L->size)
        return true;
    else
        return false;
}

bool IsListEmpty(ArrayList *L)
{
    if(L->length <= 0)
        return true;
    else
        return false;
}

// 删除最后一个元素
ElemType PopList(ArrayList* L)
{
    if(IsListEmpty(L))
    {
        puts("warning: list is empty!");
        return;
    }

    ElemType value = *(L->head + L->length -1);
    L->length --;
    return value;
}

// 在指定位置插入值
void InsertList(ArrayList *L, int index, ElemType value)
{
    if(IsListFull(L))
    {
        puts("warning: list is full!");
        return;
    }

    if (index < 0 || index >= L->length)
    {
        puts("warning: index out of range!");
        return;
    }

    int i;
    for(i=L->length-1;i>=index;i--)
    {
        (L->head)[i+1] = (L->head)[i];
    }
    (L->head)[index] = value;
    L->length++;
}

// 获取线性表长度
int ListLength(ArrayList* L)
{
    return L->length;
}

// 打印线性表
void printListLength(ArrayList* L)
{
    printf("########\n");
    printf("length=%d\n", ListLength(L));
    int i;
    for(i=0; i < L->length; i++)
    {
        printf("L[%d] = %d\n", i, *(L->head + i));
    }
    printf("########\n\n");
}
