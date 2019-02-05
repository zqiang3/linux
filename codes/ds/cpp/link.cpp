#include "link.h"
using namespace std;

Node::Node(int v, Node *next)
{
    value = v;
    next = next;
}

LinkList::LinkList()
{
    len = 0;
    head = new Node;
}

int LinkList::length() const
{
    return len;
}

bool LinkList::isEmpty() const
{
    return len == 0;
}

void LinkList::append(int v)
{
    Node *cur = head;
    while(cur->next != NULL)
        cur = cur->next;
    Node *node = new Node(v);
    cur->next = node;
    len++;
    
}

void LinkList::show() const
{
    cout << "len = " << len << endl;
    Node *cur = head->next;
    while(cur)
    {
        cout << cur->value << ", ";
        cur = cur->next;
    }
    cout << endl;
}

void LinkList::insert(int i, int v)
{
    if (i >= len)
        return;

    int count = 0;
    Node *cur = head->next;
    Node *pre = head;
    while(cur)
    {
        if (count++ == i)
            break;

        pre = cur;
        cur = cur->next;
    }
    Node *node = new Node(v);
    pre->next = node;
    node->next = cur;
    len++;
    
}

int LinkList::pop()
{
    if (isEmpty())
        return 0;

    Node *pre = head;
    Node *cur = head->next;
    while(cur->next)
    {
        pre = cur;
        cur = cur->next;
    }

    int temp = cur->value;
    pre->next = NULL;
    delete cur;
    len--;

    return temp;
}

bool LinkList::find(int v)
{
    Node *cur = head->next;
    while(cur)
    {
        if (cur->value == v)
            return true;
        cur = cur->next;
    }
    return false;
}

bool LinkList::remove(int v)
{
    Node *pre = head;
    Node *cur = head->next;
    while(cur)
    {
        if (cur->value == v)
            break;

        pre = cur;
        cur = cur->next;
    }

    if (cur == NULL)
        return false;
    else
    {
        pre->next = cur->next;
        delete cur;
        len--;
        return true;
    }
}
