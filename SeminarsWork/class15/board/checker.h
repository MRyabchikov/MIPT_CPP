#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
using namespace std;

constexpr int white_color = 17;
constexpr int black_color = 30;

class Cell;

class Checker : Graph_lib::Circle
{
  public:
    enum Type
    {
        black,
        white
    };

    Checker(Simple_window& win, Checker::Type type);

    void draw_lines () const override { Circle::draw_lines(); }

    void attach (const Cell& c);

    void detach ();

    bool is_black () { return type == black; }

    bool is_white () { return type == white; }

  private:
    static constexpr int r = 0.45 * Cell::size;
    const Cell* cell = nullptr;
    Type type;
};