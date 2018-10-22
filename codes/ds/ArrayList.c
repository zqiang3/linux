#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct
{
    ElemType *head;
    int length;
    int max;
} ArrayList;

void println(char *text)
{
    printf("%s\n", text);
}


ArrayList* InitList(int size);
void AppendList(ArrayList* L, ElemType value);
ElemType PopList(ArrayList* L);
int ListLength(ArrayList* L);
void printListLength(ArrayList* L);
void InsertList(ArrayList *L, int index, ElemType value);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Usage cmd <length>\n");
        exit(1);
    }

    int len = atoi(argv[1]);
    println("init ArrayList");
    ArrayList *L = InitList(len);

    println("append 0");
    AppendList(L, 0);
    printListLength(L);

    println("append 1");
    AppendList(L, 1);
    printListLength(L);
    
    println("append 2");
    AppendList(L, 2);
    printListLength(L);

    println("pop");
    ElemType value = PopList(L);
    printListLength(L);

    println("pop");
    value = PopList(L);
    printListLength(L);

    println("insert index: 0, value: 10");
    InsertList(L, 0, 10);
    printListLength(L);

    println("insert index: 1, value: 11");
    InsertList(L, 1, 11);
    printListLength(L);

    println("insert index: 1, value: 12");
    InsertList(L, 1, 12);
    printListLength(L);


    return 0;
}


// 初始化
ArrayList* InitList(int size)
{
    ArrayList *L = (ArrayList*)malloc(sizeof(ArrayList));
    ElemType *head = (ElemType*)malloc(size * sizeof(ElemType));
    L->head = head;
    L->max= size;
    L->length= 0;
    return L;
}

// 末尾添加
void AppendList(ArrayList* L, ElemType value)
{
    if(L->length >= L->max)
    {
        printf("warning: excess length\n");
        return;
    }

    *(L->head + L->length) = value;
    L->length ++;

}

// 删除最后一个元素
ElemType PopList(ArrayList* L)
{
    if(L->length <=0)
    {
        printf("warning: no value to pop\n");
        return;
    }

    ElemType value = *(L->head + L->length -1);
    L->length --;
    return value;
}

// 在指定位置插入值
void InsertList(ArrayList *L, int index, ElemType value)
{
    if (index < 0 || index >= L->length || L->length + 1 > L->max)
    {
        printf("warning: index out of range\n");
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
