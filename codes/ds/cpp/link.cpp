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

LinkList::LinkList(int arr[], int count)
{
    len = 0;
    head = new Node;
    for (int i = 0; i < count; i++)
        append(arr[i]);
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
    cout << "[";
    while(cur)
    {
        cout << cur->value << ", ";
        cur = cur->next;
    }
    cout << "\b\b]\n";
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

int& LinkList::operator[](int i)
{
    if (i >= len)
    {
        int *temp = new int;
        return *temp;
    }

    int count = 0;
    Node *cur = head->next;
    while(count++ != i)
        cur = cur->next;

    return cur->value;
}


LinkList& LinkList::operator+(LinkList &o)
{
    LinkList *r = new LinkList();
    Node *cur = head->next;
    Node *ocur = o.head->next;
    int temp;
    while(cur || ocur)
    {
        temp = 0;
        if (cur && ocur)
            temp = cur->value + ocur->value;
        else if (cur)
            temp = cur->value;
        else if (ocur)
            temp = ocur->value;
        else
            ;

        r->append(temp);
        if (cur)
            cur = cur->next;
        if (ocur)
            ocur = ocur->next;
    }

    return *r;
}
