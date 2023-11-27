#include "vector.h"
#include <iostream>
using namespace std;

int main (void)
{
    Vector v(3);
    for (int i = 0; i < 3; i++)
        v.set(i, i + 1);
    for (int i = 0; i < 3; i++)
        cout << v.get(i) << " ";
    return 0;
}