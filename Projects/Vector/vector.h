#pragma once
#include <initializer_list>
#include <iostream>

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

    int size () const { return sz; }

    double& operator[] (int i) { return elem[i]; }

    double operator[] (int i) const { return elem[i]; }

  private:
    int sz;
    double* elem;
};