#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
    ElemType value;
    struct Node *next;
}Node;

typedef struct
{
    Node *head;
}LinkList;

LinkList* InitList();
ElemType GetElement(LinkList* L, int index);
void AppendList(LinkList* L, ElemType value);
ElemType PopList(LinkList *L);
void InsertList(LinkList *L, int index, ElemType value);
void printList(LinkList* L);


int main(int argc, char** argv)
{
    ElemType value;

    LinkList *L = InitList();
    value = PopList(L);

    AppendList(L, 3);
    printList(L);

    AppendList(L, 5);
    printList(L);

    value = GetElement(L, 0);
    printf("value=%d\n", value);
    value = GetElement(L, 1);
    printf("value=%d\n", value);

    printf("\n");
    InsertList(L, 0, 11);
    printList(L);
    InsertList(L, 3, 22);
    printList(L);
    InsertList(L, 5, 22);
    printList(L);


}

// 初始化
LinkList* InitList()
{
    LinkList *L = (LinkList*)malloc(sizeof(LinkList));

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = 0;
    newNode->next = NULL;
    L->head = newNode;
    return L;
}

ElemType GetElement(LinkList* L, int index)
{
    if(index < 0)
    {
        printf("warning: index less than 0\n");
        return 0;
    }

    int count = 0;
    Node *p = L->head;
    int i = 0;

    int found = 1;
    for(i = 0; i <= index; i++)
    {
        if(p->next == NULL)
        {
            found = 0;
            printf("warning: index out of range\n");
            break;
        }
        p = p->next;
    }

    if(!found)
        return 0;
    else
        return p->value;
}

// 末尾添加数据
void AppendList(LinkList* L, ElemType value)
{
    Node *p = L->head;
    while(p->next != NULL)
        p = p->next;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    p->next = newNode;
}

ElemType PopList(LinkList *L)
{
    if(L->head->next == NULL)
    {
        printf("warning: no value to pop\n");
        return 0;
    }

    Node *pre = L->head;
    Node *p = pre->next;
    while(p->next != NULL)
    {
        pre = p;
        p = p->next;
    }
    pre->next = NULL;
    return p->value;
}

void InsertList(LinkList *L, int index, ElemType value)
{
    int len = getLength(L);
    if(index < 0 || index > len)
    {
        printf("warning: index out of range\n");
        return;
    }

    if(index == len)
    {
        AppendList(L, value);
        return;
    }

    Node *p = L->head;
    int count = 0;

    while(p->next != NULL)
    {
        if(count == index)
        {
            Node *next = p->next;
            Node* new = (Node*)malloc(sizeof(Node));
            new->value = value;
            p->next = new;
            new->next = next;

        }
        p = p->next;
        count++;
    }
}

// 获取链表长度
int getLength(LinkList* L)
{
    Node *p = L->head;
    int count = 0;
    while(p->next != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

// 打印链表内容
void printList(LinkList* L)
{
    Node *p = L->head;
    int count = 0;
    printf("########\n");
    while(p->next != NULL)
    {
        count++;
        p = p->next;
        printf("index: %d, value=%d\n", count-1, p->value);
    }
    printf("########\n\n");
}
