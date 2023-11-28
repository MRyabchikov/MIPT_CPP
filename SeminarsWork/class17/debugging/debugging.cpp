#include <iostream>
#include <tracer/tracer.h>
#include <vector>
using namespace std;

int factorial (int n)
{
    TRACE_FUNC;
    if (n <= 0)
        return 1;
    return n * factorial(n - 1);
}

int main (void)
{
    TRACE_FUNC;
    factorial(5);
    return 0;
}