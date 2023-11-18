#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "cell.h"
#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
using namespace std;

using Graph_lib::Address;
using Graph_lib::Point;

class MyWindow : public Simple_window
{
  public:
    MyWindow(Point xy, int w, int h, const string title);

  private:
    Graph_lib::Button quit_button;
    static void cb_quit (Address, Address widget);
    void quit ();
};

class Chessboard : public MyWindow
{
  public:
    Chessboard(Point xy);
    static constexpr int N = 8;
    static constexpr int N_max = 8;
    static_assert(N <= N_max, "not allowed to create more than N_max * N_max fields");
    Cell& at (char c, int n);

  private:
    static constexpr int margin = 30;
    static constexpr int width = N * Cell::size + 2 * margin + 70;
    static constexpr int height = N * Cell::size + 2 * margin;
    Graph_lib::Vector_ref<Cell> cells;
    Graph_lib::Marks x_labels;
    Graph_lib::Marks y_labels;
    Cell* selected{nullptr};

    static void cb_clicked (Address, Address widget)
    {
        auto& btn = Graph_lib::reference_to<Cell>(widget);
        dynamic_cast<Chessboard&>(btn.window()).clicked(btn);
    }

    void clicked (Cell& c)
    {
        if (c.is_white())
            return;
        if (!selected)
        {
            selected = &c;
            c.activate();
        }
        else
        {
            if (selected->has_checker())
            {
                c.attach_checker(selected->detach_checker());  // Здесь можно сдеать move_figure
            }
            selected->deactivate();
            if (&c == selected)
            {
                selected = nullptr;
                return;
            }
            selected = &c;
            c.activate();
        }
        Fl::redraw();
    }
};