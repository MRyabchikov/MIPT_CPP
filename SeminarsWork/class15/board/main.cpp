#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "board.h"
#include "cell.h"
#include "checker.h"
#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
using namespace Graph_lib;

int main (void)
{
    // MyWindow win{{100, 100}, 600, 400, "MyWindow"};
    // Function line{[] (double x) {return x; }, 0, 100, Point{20, 150}, 1000, 50, 50};
    // win.attach(line);
    // Function square{[] (double x) { return x*x; }, 0, 100, Point{20, 150}, 1000, 50, 50};
    // win.attach(square);
    // Cell new_c({200, 200}, nullptr, Cell::black);
    // win.attach(new_c);
    // win.wait_for_button();
    // win.wait_for_button();
    // win.wait_for_button();
    Chessboard board({100, 100});
    Checker w(board, Checker::white);
    board.at('a', 3).attach_checker(w);
    board.wait_for_button();

    return 0;
}