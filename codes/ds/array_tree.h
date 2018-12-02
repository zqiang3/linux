typedef int ElemType;

typedef struct
{
    int size;
    ElemType *arr;
    
}Tree;

Tree* genTree(int size);
void append_tree(Tree* tree, ElemType value);
void tranverse_tree(Tree* tree);
