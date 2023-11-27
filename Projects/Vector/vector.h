#pragma once
#include <iostream>

class Vector
{
  public:
    Vector(int s);
    ~Vector();

    int size () const { return sz; }

    double get (int n) { return elem[n]; }

    void set (int n, double value) { elem[n] = value; }

  private:
    int sz;
    double* elem;
};