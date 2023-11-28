#pragma once
#include <initializer_list>
#include <iostream>
#include <tracer/tracer.h>

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

    int size () const;

    double& operator[] (int i);

    double operator[] (int i) const;

  private:
    int sz;
    double* elem;
};