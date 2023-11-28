#include "vector.h"
#include <iostream>

using namespace std;

Vector::Vector(int size) : sz(size), elem(new double[size])
{
    for (int i = 0; i < sz; i++)
        elem[i] = 0;
}

Vector::Vector(initializer_list<double> lst) : sz(lst.size()), elem(new double[lst.size()])
{
    copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& obj) : sz(obj.size()), elem(new double[obj.size()])
{
    copy(obj.elem, obj.elem + obj.sz, elem);
}

Vector::~Vector() { delete[] elem; }

Vector& Vector::operator= (const Vector& obj)
{
    double* p = new double[obj.sz];
    copy(obj.elem, obj.elem + obj.sz, p);
    delete[] elem;
    elem = p;
    sz = obj.sz;
    return *this;
}

Vector::Vector(Vector&& obj) : sz(obj.sz), elem(obj.elem)
{
    obj.sz = 0;
    obj.elem = nullptr;
}

Vector& Vector::operator= (Vector&& obj)
{
    delete[] elem;
    elem = obj.elem;
    sz = obj.sz;
    obj.sz = 0;
    obj.elem = nullptr;
    return *this;
}
