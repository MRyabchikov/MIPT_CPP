#include "vector.h"
#include <iostream>
#include <memory>
#include <tracer/tracer.h>

using namespace std;

template <typename T, typename A> Vector<T, A>::Vector(A alloc) : Vector_Base<T, A>(alloc, 0) {}

template <typename T, typename A> Vector<T, A>::Vector(int size, T def, A alloc) : Vector_Base<T, A>(alloc, size)

{
    TRACE_FUNC;
    for (int i = 0; i < this->sz; i++)
        this->alloc.construct(&(this->elem[i]), def);
}

template <typename T, typename A>
Vector<T, A>::Vector(initializer_list<T> lst, A alloc) : Vector_Base<T, A>(alloc, lst.size())
{
    TRACE_FUNC;
    for (size_t i = 0; i < lst.size(); i++)
        this->alloc.construct(&(this->elem[i]), *(lst.begin() + i));
}

template <typename T, typename A> Vector<T, A>::Vector(const Vector& obj) : Vector_Base<T, A>(obj.alloc, obj.size())
{
    TRACE_FUNC;
    for (int i = 0; i < obj.size(); i++)
        this->alloc.construct(&(this->elem[i]), obj.elem[i]);
}

template <typename T, typename A> Vector<T, A>::~Vector()
{
    TRACE_FUNC;
    for (int i = 0; i < this->sz; i++)
        this->alloc.destroy(&(this->elem[i]));
}

template <typename T, typename A> Vector<T, A>& Vector<T, A>::operator= (const Vector& obj)
{
    TRACE_FUNC;
    if (this == &obj)
        return *this;
    Vector_Base<T, A> b(this->alloc, obj.sz);
    uninitialized_copy(b.elem, b.elem + b.sz, obj.elem);
    for (int i = 0; i < this->sz; i++)
        this->alloc.destroy(&(this->elem[i]));
    swap<Vector_Base<T, A>>(*this, b);
    for (int i = 0; i < b.sz; i++)
        b.alloc.destroy(&(b.elem[i]));
    return *this;
}

template <typename T, typename A> Vector<T, A>::Vector(Vector&& obj) : Vector_Base<T, A>(obj.alloc, obj.sz)
{
    TRACE_FUNC;
    Vector_Base<T, A> b(this->alloc, 0);
    swap<Vector_Base<T, A>>(obj, b);
    for (size_t i = 0; i < b.sz; i++)
        b.alloc.destroy(&(b.elem[i]));
}

template <typename T, typename A> Vector<T, A>& Vector<T, A>::operator= (Vector&& obj)
{
    TRACE_FUNC;
    Vector_Base<T, A> b(obj.alloc, obj.sz);
    swap<Vector_Base<T, A>>(*this, b);
    for (int i = 0; i < b.sz; i++)
        b.alloc.destroy(&(b.elem[i]));
    Vector_Base<T, A> tmp(obj.alloc, 0);
    swap<Vector_Base<T, A>>(obj, b);
    for (int i = 0; i < tmp.sz; i++)
        tmp.alloc.destroy(&(tmp.elem[i]));
    return *this;
}

template <typename T, typename A> int Vector<T, A>::size() const
{
    TRACE_FUNC;
    return this->sz;
}

template <typename T, typename A> int Vector<T, A>::capacity() const
{
    TRACE_FUNC;
    return this->space;
}

template <typename T, typename A> T& Vector<T, A>::operator[] (int i)
{
    TRACE_FUNC;
    return this->elem[i];
}

template <typename T, typename A> const T& Vector<T, A>::operator[] (int i) const
{
    TRACE_FUNC;
    return this->elem[i];
}

template <typename T, typename A> void Vector<T, A>::reserve(int newalloc)
{
    TRACE_FUNC;
    if (newalloc <= this->space)
        return;
    Vector_Base<T, A> b(this->alloc, newalloc);
    uninitialized_copy(b.elem, &(b.elem[this->sz]), this->elem);
    for (int i = 0; i < b.sz; i++)
        cerr << b.elem[i] << " ";
    for (int i = 0; i < this->sz; i++)
        this->alloc.destroy(&(this->elem[i]));
    swap(this->elem, b.elem);
    swap(this->sz, b.sz);
    swap(this->space, b.space);
}

template <typename T, typename A> void Vector<T, A>::resize(int new_size, T def)
{
    TRACE_FUNC;
    reserve(new_size);
    for (int i = this->sz; i < new_size; i++)
        this->alloc.construct(&(this->elem[i]), def);
    for (int i = this->sz; i < new_size; i++)
        this->alloc.destruct(&(this->elem[i]));
    this->sz = new_size;
}

template <typename T, typename A> void Vector<T, A>::push_back(const T& new_value)
{
    TRACE_FUNC;
    if (this->space == 0)
        reserve(_initial_size);
    else if (this->sz == this->space)
        reserve(2 * this->space);
    this->alloc.construct(&(this->elem[this->sz++]), new_value);
}

template <typename T, typename A> T& Vector<T, A>::at(int i)
{
    if (i < 0 || i >= this->sz)
        throw out_of_range();
    return this->elem[i];
}

template <typename T, typename A> const T& Vector<T, A>::at(int i) const
{
    if (i < 0 || i >= this->sz)
        throw out_of_range();
    return this->elem[i];
}
