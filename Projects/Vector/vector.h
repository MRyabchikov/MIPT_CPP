#pragma once
#include <initializer_list>
#include <iostream>
#include <memory>
#include <tracer/tracer.h>

constexpr int _initial_size = 2;

template <typename T, typename A> struct Vector_Base
{
    A alloc;
    T* elem;
    int sz;
    int space;

    Vector_Base(A a, int n) : alloc{a}, elem{a.allocate(n)}, sz{n}, space{n} { TRACE_FUNC; }

    ~Vector_Base() { alloc.deallocate(elem, space); }
};

template <typename T, typename A = std::allocator<T>> class Vector : private Vector_Base<T, A>
{
  public:
    Vector(A alloc = A());
    explicit Vector(int s, T def = T(), A alloc = A());
    ~Vector();
    Vector(std::initializer_list<T> lst, A alloc = A());
    Vector(const Vector& obj);
    Vector(Vector&& a);
    Vector& operator= (Vector&& obj);
    Vector& operator= (const Vector& obj);
    void resize (int new_size, T def = T());
    void push_back (const T& new_elem);

    int size () const;
    int capacity () const;

    T& operator[] (int i);
    T& at (int i);

    const T& at (int i) const;
    const T& operator[] (int i) const;

    void reserve (int newalloc);
};
