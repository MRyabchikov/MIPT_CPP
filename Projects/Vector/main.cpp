#include "vector.h"
#include <iostream>
#include <memory>
#include <tracer/tracer.h>
using namespace std;

template <typename T> ostream& operator<< (ostream& fout, const Vector<T>& v)
{
    TRACE_FUNC;
    for (int i = 0; i < v.size(); i++)
        fout << v[i] << " ";
    return fout;
}

Vector<double> init_vec ()
{
    TRACE_FUNC;
    return {1.4, 2.1, 3.9};
}

int main (void)
{
    TRACE_FUNC;
    Vector<Vector<int>> v1;
    cout << "Default initialization: " << v1 << endl;
    Vector<int> v2 = {1, 2, 3};
    cout << "Initializer list inititalization: " << v2 << endl;
    Vector<double> v3(4);
    cout << "Initialization with size 4: " << v3 << endl;
    Vector<double> v4(v3.size());
    cout << "Intitialization with copy constructor: " << v4 << endl;
    Vector<double> v5(move(init_vec()));
    cout << "Inititalization with moving constructor: " << v5 << endl;
    Vector<int> v6;
    v6 = v2;
    cout << "Now v6 is equal to v2: " << v6 << endl;
    for (int i = 0; i < 4; i++)
        v2.push_back(i + 4);
    cout << "v2 after pushing back some values: " << v2 << endl;
    v1.push_back(v2);
    v1.push_back(v2);
    cout << "Vector of vectors: " << v1 << endl;
    cout << "v2 size: " << v2.size() << "; v2 capacity: " << v2.capacity() << endl;
    try
    {
        cout << v1.at(3);
    }
    catch (out_of_range&)
    {
        cout << "Blocked index error" << endl;
    }
    return 0;
}