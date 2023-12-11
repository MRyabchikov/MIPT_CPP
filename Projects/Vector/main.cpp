#include "vector.h"
#include <iostream>
#include <tracer/tracer.h>
using namespace std;

Vector init_vec () { return {1, 2, 3}; }

int main (void)
{
    TRACE_FUNC;
    Vector v1(3);
    Vector v2{1, 2, 3};
    const Vector v3{v2};
    cout << v1.size() << endl;
    cout << v1[0] << " " << v3[1] << endl;
    v2 = v3;
    v2 = init_vec();

    return 0;
}