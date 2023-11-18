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

class Checker;

class Cell : public Graph_lib::Button
{
  public:
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

    bool has_checker () const { return check != nullptr; }

    void attach_checker (Checker& c);

    const Checker& get_checker () const;

    Checker& detach_checker ();
    Point center () const;

    static constexpr int size = 80;

  private:
    Type type;
    void reset_color ();
    Checker* check = nullptr;
};