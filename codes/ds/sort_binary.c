#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


void add_values(ElemType *arr, int size,  Tree *tree)
{
    int i;
    for(i = 0; i < size; i++)
    {
        append_tree(tree, arr[i]);
    }
}

typedef struct LinkNode
{
    Node* value;
    struct LinkNode *next;
}LinkNode;


typedef struct
{
    LinkNode* head;
}LinkList;
void deep_tranverse(Tree *tree);
void _deep_tranverse(LinkList *list);

void append_link(LinkList *list, Node *value)
{
    if(!value)
        return;

    LinkNode *head = list->head;
    LinkNode *node = (LinkNode*)malloc(sizeof(LinkNode));
    node->value = value;
    node->next = NULL;

    if(!list->head)
    {
        list->head = node;
        return;
        
    }

    LinkNode *cur = list->head;
    while(cur->next)
        cur = cur->next;

    cur->next = node;
}

LinkList* create_link_list()
{
    LinkList *list = (LinkList*)malloc(sizeof(LinkList));
    list->head = NULL;
    return list;
}

int main(int argc, char** argv)
{
    Tree* tree = init_tree();
    ElemType arr[] = 
    {
        10, 3, 18, 2, 4, 13, 21, 9, 8, 9
    };
    int size = sizeof(arr) / sizeof(ElemType);
    add_values(arr, size, tree);
    deep_tranverse(tree);

    delete_tree(tree, 10);
    deep_tranverse(tree);

    delete_tree(tree, 4);
    deep_tranverse(tree);

}

void deep_tranverse(Tree *tree)
{
    printf("deep begin\n");
    if(!tree->head)
        return;
        
    LinkList* list = create_link_list();
    append_link(list, tree->head);
    _deep_tranverse(list);
    printf("\n\n");
}

void _deep_tranverse(LinkList *list)
{
    if(!list->head)
        return;

    LinkNode* cur = list->head;
    LinkList* new_list = create_link_list();

    Node *node;
    while(cur)
    {
        node = cur->value;
        printf("%d ", node->value);
        append_link(new_list, node->left);
        append_link(new_list, node->right);
        cur = cur->next;
    }
    printf("\n");


    _deep_tranverse(new_list);
}


