#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <iostream>
#include <polygon/poly.h>
#include <vector2d/vector2d.h>
using namespace std;
using namespace Graph_lib;

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

int main (void)
{
    Simple_window win(Point{100, 100}, 400, 400, "sem11");
    MyArc arc(Point{200, 200}, 100, 50, 0, 180);
    arc.set_fill_color(Color::red);
    arc.set_color(Color::blue);
    win.attach(arc);
    win.wait_for_button();
    return 0;
}