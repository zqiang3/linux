#include "array_tree.h"


int main(int argc, char *argv[])
{
    Tree *tree = genTree(10);
    append_tree(tree, 3);
    append_tree(tree, 5);
    tranverse_tree(tree);

    return 0;

}
