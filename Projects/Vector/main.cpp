#include "vector.cpp"
#include "vector.h"
#include <iostream>
#include <memory>
#include <tracer/tracer.h>
using namespace std;

template <typename T> ostream& operator<< (ostream& fout, const Vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
        fout << v[i] << " ";
    return fout;
}

int main (void)
{
    TRACE_FUNC;
    Vector<int> a{0, 1, 2, 3};
    Vector<Vector<int>> v1;
    Vector<int> v2 = {1, 2, 3};
    cout << v2 << endl;
    for (int i = 0; i < 3; i++)
        v2.push_back(i + 4);
    cout << v2;
    // v1.push_back(v2);
    // v1.push_back(v2);
    return 0;
}