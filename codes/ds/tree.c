#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


void delete_tree(Tree* tree, ElemType value)
{
    Node *cur = head;
    Node *found = NULL;
    Node *pre = NULL;
    while(cur)
    {
        pre = cur;
        if(value == cur->value)
        {
            found = cur;
            break;
        }
        if(value < cur->value)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if(!found)
        return;

    if(!(found->left || found->right))
    {
        if(!pre)
            tree->head = found;

        if(value < pre->value)
            pre->left = NULL;
        else
            pre->right = NULL;
    }
    else if(found->left && !found->right)
    {
        if(!pre)
            tree->head = found->left;
        if(value < pre->value)
            pre->left = found->left;
        else
            pre->right = found->left;
    }
    else if(!found->left && found->right)
    {
        if(!pre)
            tree->head = found->right;
        if(value < pre->value)
            pre->left = found->right;
        else
            pre->right = found->right;
    }
    else
    {
        if(!pre)
            tree->head = found->right;

        if(value < pre->value)
            pre->left = found->right
        else
            pre->right = found->right;

        Node* cur = found->right;
        while(cur->left)
            cur = cur->left;

        cur->left = found->left;
    }
}


void append_tree(Tree* tree, ElemType value)
// 排序二叉树，增加节点
{
    Node *node = create_node(value);

    Node *head = tree->head;
    if(!head)
    {
        tree->head = node;
        return;
    }

    Node *cur = tree->head;
    while(1)
    {
        if(value < cur->value)
        {
            if(cur->left == NULL)
            {
                cur->left = node;
                break;
            }
            cur = cur->left;
        }
        else
        {
            if(cur->right == NULL)
            {
                cur->right = node;
                break;
            }
            cur = cur->right;
        }
    }
}

Node* create_node(ElemType value)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right= NULL;
    return node;
}


void _tranverse_tree(Node* p)
{
    if(!p)
        return;

    if(p->left)
        _tranverse_tree(p->left);
    printf("%d\n", p->value);
    if(p->right)
        _tranverse_tree(p->right);
}

void tranverse_tree(Tree *tree)
{
    _tranverse_tree(tree->head);
}

Tree* init_tree()
{
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    tree->head = NULL;
    return tree;
}
