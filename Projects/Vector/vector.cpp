#include "vector.h"
#include <iostream>

using namespace std;

Vector::Vector(int size) : sz(size), elem(new double[size])
{
    for (int i = 0; i < sz; i++)
        elem[i] = 0;
}

Vector::~Vector() { delete[] elem; }
