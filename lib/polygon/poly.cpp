#include "poly.h"
#include <cmath>

list<Vector2d> regular_polygon (int n, Vector2d center, double radius, double phi_0)
{
    if (n <= 2)
        throw runtime_error("Invalid ammount of vertexes");
    if (radius <= 0)
        throw runtime_error("Invalid radius");
    Vector2d v(radius, 0.);
    list<Vector2d> poly;
    for (int i = 0; i < n; i++)
    {
        double phi = 2. * acos(-1) * i / n;
        Vector2d q = v.rotate(phi_0 + phi);
        poly.push_back(q + center);
    }
    return poly;
}

Vector2d lerp (Vector2d a, Vector2d b, double t) { return a + (b - a) * t; };