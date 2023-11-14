#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "cell.h"
#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
using namespace Graph_lib;

Cell::Cell(Point xy, Callback cb, Type t) : Button{xy, size, size, "", cb}, type(t) {}

void Cell::reset_color()
{
    if (!pw)
        throw runtime_error("Cell is not attached to a window");
    if (is_black())
        pw->color(Color::black);
    else
        pw->color(Color::white);
}

void Cell::attach(Graph_lib::Window& win)
{
    Button::attach(win);
    reset_color();
}