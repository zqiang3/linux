typedef int ElemType;

typedef struct Node
{
    ElemType value;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct
{
    Node *head;
}Tree;

Tree* init_tree();
Node* create_node(ElemType value);
void append_tree(Tree* tree, ElemType value);
void tranverse_tree(Tree* tree);
void delete_tree(Tree* tree, ElemType value);
