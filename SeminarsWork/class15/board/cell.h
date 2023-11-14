#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
using namespace std;

using Graph_lib::Point;

struct Cell : Graph_lib::Button
{
    enum Type
    {
        black,
        white
    };

    Cell(Point xy, Graph_lib::Callback cb, Type t);

    bool is_black () const { return type == black; }

    bool is_white () const { return type == white; }

    void activate ()
    {
        if (pw)
            pw->color(FL_SELECTION_COLOR);
    }

    void deactivate () { reset_color(); }

    void attach (Graph_lib::Window& win) override;

    static constexpr int size = 100;

  private:
    Type type;
    void reset_color ();
};