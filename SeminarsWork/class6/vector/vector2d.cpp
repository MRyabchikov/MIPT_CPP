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

int main (void)

{
    Vector2d v1, v2;
    cin >> v1 >> v2;
    v1 -= v2;
    cout << v1;
}