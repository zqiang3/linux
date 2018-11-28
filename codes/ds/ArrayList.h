#ifndef _ARRAYLIST_H
    #define _ARRAYLIST_H
#endif

#include <stdbool.h>

typedef int ElemType;
typedef struct
{
    ElemType *head;
    int length;
    int size;
} ArrayList;

ArrayList* MakeArrayList(void);
void InitList(ArrayList *L, int size);
bool IsListEmpty(ArrayList*);
bool IsListFull(ArrayList*);
void AppendList(ArrayList* L, ElemType value);
ElemType PopList(ArrayList* L);
int ListLength(ArrayList* L);
void printListLength(ArrayList* L);
void InsertList(ArrayList *L, int index, ElemType value);
