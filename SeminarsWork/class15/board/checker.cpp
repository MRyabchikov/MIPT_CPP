#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "cell.h"
#include "checker.h"
#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
using namespace Graph_lib;
using namespace std;

Checker::Checker(Simple_window& win, Checker::Type t) : Circle({0, 0}, r), type(t)
{
    win.attach(*this);
    if (type == Checker::white)
        set_fill_color(Color{white_color});
    else
    {
        set_fill_color(Color{black_color});
    }
}

void Checker::attach(const Cell& c)
{
    move(c.center().x - center().x, c.center().y - center().y);
    cell = &c;
}

void Checker::detach() { cell = nullptr; }