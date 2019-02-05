#include <iostream>
using namespace std;


class Node
{
public:
    int value;
    Node *next;
    Node(int v = 0, Node *next = NULL);
};

class LinkList
{
private:
    int len;
    Node *head;
public:
    LinkList();
    int length() const;
    bool isEmpty() const;
    void append(int v);
    void insert(int i, int v);
    int pop();
    void show() const;
    bool find(int v);
    bool remove(int v);
};
