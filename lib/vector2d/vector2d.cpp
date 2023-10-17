#include "vector2d.h"
#include <iostream>
using namespace std;

Vector2d operator+ (const Vector2d& v1, const Vector2d& v2)
{
    return Vector2d(v1.getX() + v2.getX(), v1.getY() + v2.getY());
}

Vector2d& operator+= (Vector2d& v1, const Vector2d& v2)
{
    v1 = v1 + v2;
    return v1;
}

Vector2d operator- (const Vector2d& v1) { return Vector2d(-v1.getX(), -v1.getY()); }

Vector2d operator- (const Vector2d& v1, const Vector2d& v2) { return v1 + (-v2); }

Vector2d& operator-= (Vector2d& v1, const Vector2d& v2)
{
    v1 = v1 - v2;
    return v1;
}

Vector2d operator* (const Vector2d& v, double x) { return Vector2d(v.getX() * x, v.getY() * x); }

Vector2d operator* (double x, const Vector2d& v) { return v * x; }

Vector2d& operator*= (Vector2d& v, double x)
{
    v = v * x;
    return v;
}

double length (const Vector2d& v) { return sqrt(v.getX() * v.getX() + v.getY() * v.getY()); }

ostream& operator<< (ostream& fout, const Vector2d& v1)
{
    fout << v1.getX() << " " << v1.getY();
    return fout;
}

istream& operator>> (istream& fin, Vector2d& v1)
{
    double x, y;
    fin >> x >> y;
    v1.setX(x);
    v1.setY(y);
    return fin;
}

Vector2d Vector2d::rotate(double phi, Vector2d center) const
{
    Vector2d r = {*this - center};
    return center + Vector2d(r.x * cos(phi) - r.y * sin(phi), r.x * sin(phi) + r.y * cos(phi));
}

// int main (void)

// {
//     Vector2d v1, v2;
//     cin >> v1 >> v2;
//     (v1 -= v2) += v2;
//     cout << v1;
// }