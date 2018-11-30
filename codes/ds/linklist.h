#include <stdbool.h>

typedef struct
{
    char name[100];
    int age;
}Item;

typedef struct node
{
    Item item;
    struct node *fwd;
    struct node *bwd;
}Node;

typedef struct list
{
    Node *root;
}List;

List* GenAndInitList();
bool OrderedInsert(List *list, Item item, int (*compare)(void* a, void *b));
void printList(List *list, void (*print)(void *));
