#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node* left;
    struct Node* right;
}Node;

void appendTree(Node* parent, int is_left, ElemType data);
void tranverseTree(Node* root);


int main(int argc, char **agrv)
{
    Node *cur;
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = 0;

    cur = root;
    appendTree(cur, 1, 10);
    cur = cur->left;
    appendTree(cur, 0, 20);
    cur = cur->right;
    appendTree(cur, 1, 30);

    tranverseTree(root);
}


void appendTree(Node* parent, int is_left, ElemType data)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->left = NULL;
    p->right= NULL;
    if(is_left)
        parent->left = p;
    else
        parent->right = p;
}


void tranverseTree(Node* p)
{
    if(!p)
        return;

    if(p->left)
        tranverseTree(p->left);
    printf("%d\n", p->data);
    if(p->right)
        tranverseTree(p->right);
}
