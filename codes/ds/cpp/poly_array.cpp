#include "poly_array.h"

void Poly::init()
{
    high = 0;
    for (int i = 0; i < MAX; i++)
        array[i] = 0;
}

void Poly::print()
{
    cout << '[';
    for (int i = 0; i < high; i++)
        cout << array[i] << ", ";
    cout << ']';
}

void Poly::append(int c)
{
    array[high++] = c;
}

Poly& Poly::operator+(Poly &p)
{
    high = max(high, p.high);
    for (int i = 0; i < high; i++)
    {
        array[i] = array[i] + p.array[i];
    }
}
