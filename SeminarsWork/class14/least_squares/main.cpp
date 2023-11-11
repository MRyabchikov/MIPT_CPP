#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

#include "least_squares.h"

using namespace Graph_lib;
using namespace std;

int main ()
try
{
    constexpr int xmax = 600;  // window size
    constexpr int ymax = 450;
    constexpr int xoffset = 40;
    constexpr int yoffset = 40;
    constexpr int xlength = xmax - xoffset;
    constexpr int ylength = ymax - 2 * yoffset;
    constexpr int xrange = 10;
    constexpr int yrange = 10;
    constexpr int x_data_range = 10;
    Point orig{xoffset, ymax - yoffset};

    Point lt{100, 100};  // left top window corner
    Simple_window win{lt, xmax, ymax, "Least Squares"};
    Axis x{Axis::x, orig, xlength, xrange, "x"};
    Axis y{Axis::y, orig, ylength, yrange, "y"};
    win.attach(x);
    win.attach(y);

    vector<lsm::Point> data = {{1.0, 1.0}, {2.4, 3.1}, {3.5, 4.8}, {4.0, 6.1}, {5.0, 7.1}};
    Marks scatter("o");
    auto to_axis_space = [&] (lsm::Point p) -> Point
    {
        p.x *= xlength / xrange;
        p.y *= -ylength / yrange;
        p.x += orig.x;
        p.y += orig.y;
        return {int(p.x), int(p.y)};
    };
    for (auto p : data)
        scatter.add(to_axis_space(p));
    win.attach(scatter);

    auto coeffs = lsm::least_squares(data);
    Function line{[coeffs] (double x) { return coeffs.a + coeffs.b * x; },
                  0,
                  x_data_range,
                  orig,
                  2,
                  xlength / x_data_range,
                  ylength / x_data_range};
    win.attach(line);
    win.color(Color::white);
    win.wait_for_button();
}
catch (std::exception& e)
{
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
}
