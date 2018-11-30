#include "linklist.h"
#include <stdlib.h>
#include <stdio.h>

List* GenAndInitList()
{
    List *list = (List*)malloc(sizeof(List));
    if(!list)
    {
        perror("malloc List");
        return NULL;
    }
    Node *root = (Node*)malloc(sizeof(Node));
    if(!root)
    {
        perror("malloc Node");
        return NULL;
    }
    else
    {
        root->fwd = NULL;
        root->bwd = NULL;
    }

    list->root = root;
    return list;
}

bool OrderedInsert(List *list, Item item, int(*comp)(void* a, void *b))
{
    Node *root = list->root;

    Node *pre = root;
    Node *cur = root->fwd;
    while(cur && comp(&cur->item, &item) < 0)
    {
        pre = cur;
        cur = cur->fwd;
    }
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->item = item;

    pre->fwd = newnode;
    newnode->bwd = pre;
    newnode->fwd = cur;
    if(cur != NULL)
    {
        cur->bwd = newnode;
    }
    else
    {
        root->bwd = newnode;
    }

    
    return true;
}

void printList(List *list, void (*print)(void *))
{

    Node *cur = list->root->fwd;
    while(cur)
    {
        print(&cur->item);
        cur = cur->fwd;
    }
    printf("---------------------------------\n\n");
}
