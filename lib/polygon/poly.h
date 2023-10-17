#pragma once
#include <list>
#include <vector2d/vector2d.h>
using namespace std;

list<Vector2d> regular_polygon (int n, Vector2d center, double radius, double phi_0);
list<Vector2d> regular_poligon_without_one_vertexe (int n, Vector2d center, double radius, double phi_0);

Vector2d lerp (Vector2d a, Vector2d b, double t);