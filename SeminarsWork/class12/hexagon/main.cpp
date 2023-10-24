#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <iostream>
#include <polygon/poly.h>
#include <vector2d/vector2d.h>
using namespace std;
using namespace Graph_lib;

Point as_point (const Vector2d& v) { return Point(int(round(v.getX())), int(round(v.getY()))); }

class Regular_hexagon : public Shape
{
  public:
    Regular_hexagon(Point c, int r);

    Point center () const { return c; }

    int width () const { return w; }

    int height () const { return h; }

    int side_length () const { return a; }

    void draw_lines () const override;

  private:
    Point c;
    int w, h, a;
};

Regular_hexagon::Regular_hexagon(Point c, int r)
{
    auto points = regular_polygon(6, Vector2d(c.x, c.y), r, 0);
    for (auto p : points)
        add(as_point(p));
    w = 2 * r;
    h = r * sqrt(3);
    a = r;
}

void Regular_hexagon::draw_lines() const
{
    if (fill_color().visibility())
    {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for (int i = 0; i < number_of_points(); ++i)
        {
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());
    }

    if (color().visibility())
        Shape::draw_lines();
    if (color().visibility())
        fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
}

class Hexagon_tile : public Rectangle
{
  public:
    Hexagon_tile(Point p, int ww, int hh, int rr);
    void move (int dx, int dy);
    void draw_lines () const override;

  private:
    Vector_ref<Regular_hexagon> tile;
};

// Unfinished
// Hexagon_tile::Hexagon_tile(Point p, int ww, int hh, int rr) : Rectangle(p, ww, hh) { ; }

int main (void)
{
    Regular_hexagon hex({300, 400}, 100);
    Simple_window win({100, 100}, 1000, 1000, "Hexagon");
    hex.set_color(Color::red);
    hex.set_fill_color(Color::yellow);
    win.attach(hex);
    win.wait_for_button();
}