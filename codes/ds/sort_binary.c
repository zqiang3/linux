#include <stdio.h>
#include "tree.h"

int main(int argc, char** argv)
{
    Tree* tree = init_tree();
    tranverse_tree(tree);
    append_tree(tree, 20);
    append_tree(tree, 2);
    append_tree(tree, 2);
    append_tree(tree, 21);
    append_tree(tree, 2);
    append_tree(tree, 12);
    tranverse_tree(tree);

}
