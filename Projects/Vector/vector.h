#pragma once
#include <initializer_list>
#include <iostream>
#include <tracer/tracer.h>

constexpr int _initial_size = 2;

class Vector
{
  public:
    explicit Vector(int s);
    ~Vector();
    Vector(std::initializer_list<double> lst);
    Vector(const Vector& obj);
    Vector(Vector&& a);
    Vector& operator= (Vector&& obj);
    Vector& operator= (const Vector& obj);
    void resize (int new_size);
    void push_back (double new_elem);

    int size () const;
    int capacity () const;

    double& operator[] (int i);

    double operator[] (int i) const;

    void reserve (int newalloc);

  private:
    int sz;
    double* elem;
    int space;
};