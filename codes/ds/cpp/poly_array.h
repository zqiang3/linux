#include <iostream>
using namespace std;


class Poly
{
private:
    enum {
        MAX = 100,
    };
    int array[MAX + 1];
    int high;
public:
    void init();
    void print();
    void append(int);
    Poly& operator+(Poly &p);
};
