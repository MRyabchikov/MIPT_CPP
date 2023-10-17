#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <polygon/poly.h>
#include <vector2d/vector2d.h>

using namespace std;
using namespace Graph_lib;

Point as_point (const Vector2d& v) { return Point(int(round(v.getX())), int(round(v.getY()))); }

void append (Closed_polyline& poly, const list<Vector2d>& points)
{
    for (const auto& point : points)
    {
        poly.add(as_point(point));
    }
}

void append (Open_polyline& poly, const list<Vector2d>& points)
{
    for (const auto& point : points)
    {
        poly.add(as_point(point));
    }
}

void koch_fractal_step (list<Vector2d>& curve)
{
    if (curve.begin() == curve.end())
        throw runtime_error("empty curve");
    auto prev = --curve.end();
    for (auto curr = curve.begin(); curr != curve.end(); curr++)
    {
        auto p = lerp(*prev, *curr, 1. / 3);
        auto q = lerp(*prev, *curr, 2. / 3);
        auto m = p.rotate(pi / 3., q);
        curve.insert(curr, p);
        curve.insert(curr, m);
        curve.insert(curr, q);
        prev = curr;
    }
}

void dragon_fractal_step (list<Vector2d>& curve)
{
    if (curve.begin() == curve.end())
        throw runtime_error("empty curve");
    auto prev = --curve.end();
    for (auto curr = curve.begin(); curr != curve.end(); curr++)
    {
        auto p = (*curr).rotate(pi / 4, *prev);
        curve.insert(curr, p);
        prev = curr;
    }
}

double max_edge_len (const list<Vector2d>& polygon)
{
    if (polygon.begin() == polygon.end())
        throw std::runtime_error("Empty line");
    double max_len = 0.0;
    auto prev = --polygon.end();
    for (auto curr = polygon.begin(); curr != polygon.end(); curr++)
    {
        max_len = max(length(*curr - *prev), max_len);
        prev = curr;
    }
    return max_len;
}

void draw_koch_snowflake (int w, int n)
{
    Simple_window win{Point(100, 100), w, w, "Koch snowflake"};
    Vector2d c{w / 2., w / 2.};
    double r = {0.85 * w / 2.};
    auto ngon = regular_polygon(n, c, r, -pi / 2);
    Text n_steps = {as_point(c), "0"};
    n_steps.set_color(Color::blue);
    win.attach(n_steps);
    for (bool is_fine = false; !is_fine;)
    {
        Closed_polyline curve;
        append(curve, ngon);
        curve.set_color(Color::blue);
        koch_fractal_step(ngon);
        is_fine = max_edge_len(ngon) < 1.0;
        if (is_fine)
            n_steps.set_color(Color::red);
        win.attach(curve);
        win.wait_for_button();
        win.detach(curve);
        n_steps.set_label(to_string(stoi(n_steps.label()) + 1));
    }
}

void draw_dragon (int w, int n)
{
    Simple_window win{Point(100, 100), w, w, "Dragon"};
    Vector2d c{w / 2., w / 2.};
    double r = {0.85 * w / 2.};
    auto ngon = regular_poligon_without_one_vertexe(n, c, r, -pi / 2);
    Text n_steps = {as_point(c), "0"};
    n_steps.set_color(Color::blue);
    win.attach(n_steps);
    for (bool is_fine = false; !is_fine;)
    {
        Open_polyline curve;
        append(curve, ngon);
        curve.set_color(Color::blue);
        dragon_fractal_step(ngon);
        is_fine = max_edge_len(ngon) < 1.0;
        if (is_fine)
            n_steps.set_color(Color::red);
        win.attach(curve);
        win.wait_for_button();
        win.detach(curve);
        n_steps.set_label(to_string(stoi(n_steps.label()) + 1));
    }
}

int main (void)
{
    draw_koch_snowflake(800, 3);
    return 0;
}