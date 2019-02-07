#include "link2.h"
#include <cmath>
using namespace std;


ostream & operator<<(ostream &os, Value &v)
{
    os << v.f;
    return os;
    
}

Value::Value(float v)
{
    f = v;
}

bool Value::operator==(Value &o)
{
    if ( abs(this->f - o.f) < 0.000001)
        return true;
    else
        return false;
}

Value Value::operator+(Value &o)
{
    Value *r = new Value;
    r->f = this->f + o.f;
    return *r;
}

Node::Node()
{
    value = Value(0);
    next = NULL;
    
}

Node::Node(Value v, Node *next)
{
    value = v;
    next = next;
}

LinkList::LinkList()
{
    len = 0;
    head = new Node;
}

LinkList::LinkList(Value arr[], int count)
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

void LinkList::append(Value v)
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

void LinkList::insert(int i, Value v)
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

Value LinkList::pop()
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

    Value temp = cur->value;
    pre->next = NULL;
    delete cur;
    len--;

    return temp;
}

bool LinkList::find(Value v)
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

bool LinkList::remove(Value v)
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

Value& LinkList::operator[](int i)
{
    if (i >= len)
    {
        Value *v = new Value;
        return *v;
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
    Value temp;
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
