#include "vector.h"
#include <iostream>
#include <tracer/tracer.h>

using namespace std;

Vector::Vector(int size = 0) : sz(size), elem(new double[size]), space(size)
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
    if (this == &obj)
        return *this;
    if (obj.sz <= space)
    {
        for (int i = 0; i < obj.sz; i++)
            elem[i] = obj.elem[i];
        sz = obj.sz;
        return *this;
    }
    double* p = new double[obj.sz];
    for (int i = 0; i < obj.sz; i++)
        p[i] = obj.elem[i];
    delete[] elem;
    space = sz = obj.sz;
    elem = p;
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

int Vector::capacity() const { return space; }

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

void Vector::reserve(int newalloc)
{
    if (newalloc <= space)
        return;
    double* p = new double[newalloc];
    for (int i = 0; i < sz; i++)
        p[i] = elem[i];
    delete[] elem;
    elem = p;
    space = newalloc;
}

void Vector::resize(int new_size)
{
    reserve(new_size);
    for (int i = sz; i < new_size; i++)
        elem[i] = 0;
    sz = new_size;
}

void Vector::push_back(double new_value)
{
    if (space == 0)
        reserve(_initial_size);
    else if (sz == space)
        reserve(sz * 2);
    elem[sz++] = new_value;
}