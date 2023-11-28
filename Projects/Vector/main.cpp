#include "vector.h"
#include <iostream>
using namespace std;

int main (void)
{
    Vector v(3);
    for (int i = 0; i < 3; i++)
        v[i] = i + 1;
    for (int i = 0; i < 3; i++)
        cout << v[i] << " ";
    cout << endl;
    Vector v1{2, 4, 6};
    for (int i = 0; i < 3; i++)
        cout << v1[i] << " ";
    cout << endl;
    Vector v2{v1};
    v2[1] = 5;
    for (int i = 0; i < 3; i++)
        cout << v1[i] << " ";
    cout << endl;
    for (int i = 0; i < 3; i++)
        cout << v2[i] << " ";
    return 0;
}