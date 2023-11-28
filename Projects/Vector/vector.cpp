#include "vector.h"
#include <iostream>
#include <tracer/tracer.h>

using namespace std;

Vector::Vector(int size) : sz(size), elem(new double[size])
{
    TRACE_FUNC;
    for (int i = 0; i < sz; i++)
        elem[i] = 0;
}

Vector::Vector(initializer_list<double> lst) : sz(lst.size()), elem(new double[lst.size()])
{
    TRACE_FUNC;
    copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& obj) : sz(obj.size()), elem(new double[obj.size()])
{
    TRACE_FUNC;
    copy(obj.elem, obj.elem + obj.sz, elem);
}

Vector::~Vector()
{
    TRACE_FUNC;
    delete[] elem;
}

Vector& Vector::operator= (const Vector& obj)
{
    TRACE_FUNC;
    double* p = new double[obj.sz];
    copy(obj.elem, obj.elem + obj.sz, p);
    delete[] elem;
    elem = p;
    sz = obj.sz;
    return *this;
}

Vector::Vector(Vector&& obj) : sz(obj.sz), elem(obj.elem)
{
    TRACE_FUNC;
    obj.sz = 0;
    obj.elem = nullptr;
}

Vector& Vector::operator= (Vector&& obj)
{
    TRACE_FUNC;
    delete[] elem;
    elem = obj.elem;
    sz = obj.sz;
    obj.sz = 0;
    obj.elem = nullptr;
    return *this;
}

int Vector::size() const
{
    TRACE_FUNC;
    return sz;
}

double& Vector::operator[] (int i)
{
    TRACE_FUNC;
    return elem[i];
}

double Vector::operator[] (int i) const
{
    TRACE_FUNC;
    return elem[i];
}
