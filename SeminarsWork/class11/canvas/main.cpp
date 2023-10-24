#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <iostream>
#include <polygon/poly.h>
#include <vector2d/vector2d.h>
using namespace std;
using namespace Graph_lib;

Point as_point (const Vector2d& v) { return Point(int(round(v.getX())), int(round(v.getY()))); }

class MyCanvas : public Shape
{
  protected:
    void draw_lines () const override
    {
        fl_line(0, 0, 200, 200);
        fl_arc(0, 200, 100, 50, 0, 180);
    }
};

class MyArc : public Ellipse
{
  public:
    MyArc(Point p, int ww, int hh, int alpha, int beta) : Ellipse(p, ww, hh), phi1(alpha), phi2(beta){};

  protected:
    void draw_lines () const override
    {
        int w = major(), h = minor();
        if (fill_color().visibility())
        {
            fl_color(fill_color().as_int());
            fl_pie(point(0).x, point(0).y, w + w, h + h, phi1, phi2);
            fl_color(color().as_int());
        }
        if (color().visibility())
            fl_arc(point(0).x, point(0).y, w + w, h + h, phi1, phi2);
    }

  private:
    int phi1, phi2;
};

void set_up_arc (MyArc& arc) { arc.set_color(Color::blue); }

void draw_fibonacci_spiral (int w, int h, int n, double scaler)
{
    int fib1 = scaler, fib2 = scaler, direction = 0;
    Simple_window win{Point(100, 100), w, h, "Fibonacci spiral"};
    Vector2d center = {w * 0.72, h * 0.72};
    Vector_ref<MyArc> arcs;
    arcs.push_back(new MyArc{as_point(center), fib1, fib1, 180, 270});
    arcs.push_back(new MyArc{as_point(center), fib2, fib2, 270, 360});
    set_up_arc(arcs[0]);
    set_up_arc(arcs[1]);
    win.attach(arcs[0]);
    win.attach(arcs[1]);
    center = center + Vector2d(-fib1, 0);
    for (int i = 2; i <= n; i++)
    {
        fib2 = fib1 + fib2;
        fib1 = fib2 - fib1;
        switch (direction)
        {
        case 0:
            arcs.push_back(new MyArc{as_point(center), fib2, fib2, 0, 90});
            center = center + Vector2d(0, fib1);
            break;
        case 1:
            arcs.push_back(new MyArc{as_point(center), fib2, fib2, 90, 180});
            center = center + Vector2d(fib1, 0);
            break;
        case 2:
            arcs.push_back(new MyArc{as_point(center), fib2, fib2, 180, 270});
            center = center + Vector2d(0, -fib1);
            break;
        case 3:
            arcs.push_back(new MyArc{as_point(center), fib2, fib2, 270, 360});
            center = center + Vector2d(-fib1, 0);
            break;
        default:
            throw runtime_error("Unexpected value");
        }
        direction = (direction + 1) % 4;
        set_up_arc(arcs[i]);
        win.attach(arcs[i]);
    }
    win.wait_for_button();
}

int main (void)
{
    draw_fibonacci_spiral(1200, int(1220 * 0.72), 100, 1);
    return 0;
}