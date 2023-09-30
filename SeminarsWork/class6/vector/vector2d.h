#pragma once
#include <cmath>
#include <iostream>
using namespace std;

class Vector2d
{
  public:
    Vector2d(double newX = 0, double newY = 0) : x{newX}, y{newY} {}

    double getX () const { return x; }

    double getY () const { return y; }

    void setX (double newX) { x = newX; }

    void setY (double newY) { y = newY; }

  private:
    double x, y;
};

Vector2d operator+ (const Vector2d& v1, const Vector2d& v2);
Vector2d& operator+= (Vector2d& v1, const Vector2d& v2);
Vector2d operator- (const Vector2d& v1);
Vector2d operator- (const Vector2d& v1, const Vector2d& v2);
Vector2d& operator-= (Vector2d& v1, const Vector2d& v2);
Vector2d operator* (const Vector2d& v, double x);
Vector2d operator* (double x, const Vector2d& v);
Vector2d& operator*= (Vector2d& v, double x);
double length (const Vector2d& v);
ostream& operator<< (ostream& fout, const Vector2d& v1);
istream& operator>> (istream& fin, Vector2d& v1);