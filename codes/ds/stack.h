#include <stdbool.h>

typedef int ElemType;

typedef struct
{
    int size;
    int top;
    ElemType *arr;
}Stack;

Stack* genStack(int size);
void printStack(Stack *st);
void push(Stack *st, ElemType value);
void pop(void);
ElemType topElem(Stack *st);
bool isEmpty(Stack*);
bool isFull(Stack*);


