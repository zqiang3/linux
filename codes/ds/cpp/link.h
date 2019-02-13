#include <iostream>
using namespace std;

class Value
{
public:
    double coe;
    int exp;
    Value(double d, int i);
    Value();
    friend ostream & operator<<(ostream &o, Value &v);
    bool operator==(Value &o);
    Value operator+(Value &o);
    
};


class Node
{
public:
    Value value;
    Node *next;
    Node();
    Node(Value v, Node *next = NULL);
};

class LinkList
{
private:
    int len;
    Node *head;
public:
    LinkList();
    LinkList(Value arr[], int count);
    int length() const;
    bool isEmpty() const;
    void append(Value v);
    void insert(int i, Value v);
    Value pop();
    void show() const;
    bool find(Value v);
    bool remove(Value v);
    Value & operator[](int i);
    LinkList& operator+(LinkList&);
};
