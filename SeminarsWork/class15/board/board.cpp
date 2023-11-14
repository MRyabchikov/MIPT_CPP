#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "board.h"
#include "cell.h"
#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

MyWindow::MyWindow(Point xy, int w, int h, const string title)
    : Simple_window(xy, w, h, title), quit_button{Point{x_max() - 70, 20}, 70, 20, "Quit", cb_quit}
{
    attach(quit_button);
}

void MyWindow::cb_quit(Address, Address widget)
{
    auto& btn = Graph_lib::reference_to<Graph_lib::Button>(widget);
    dynamic_cast<MyWindow&>(btn.window()).quit();
}

void MyWindow::quit() { hide(); }

string letters ()
{
    string s(Chessboard::N_max, '\0');
    for (size_t i = 0; i < s.size(); i++)
        s[i] = 'a' + i;
    return s;
}

string digits ()
{
    string s(Chessboard::N_max, '\0');
    for (size_t i = 0; i < 9; i++)
        s[i] = '1' + i;
    return s;
}

Cell::Type type_of_cell (int i, int j) { return (i + j) % 2 == 0 ? (Cell::black) : (Cell::white); }

Chessboard::Chessboard(Point xy) : MyWindow(xy, width, height, "Chessboard"), x_labels(letters()), y_labels(digits())
{
    size_range(width, height, width, height);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cells.push_back(new Cell{Point{margin + j * Cell::size, margin + (N - i - 1) * Cell::size}, cb_clicked,
                                     type_of_cell(i, j)});
            attach(cells[cells.size() - 1]);
        }
    constexpr Point lb{margin + Cell::size / 2, margin + N * Cell::size + 10};
    constexpr Point rb{margin - 10, margin + N * Cell::size - Cell::size / 2};
    for (int i = 0; i < N; i++)
    {
        x_labels.add(Point{lb.x + i * Cell::size, lb.y});
        y_labels.add(Point{rb.x, rb.y - i * Cell::size});
    }
    attach(x_labels);
    attach(y_labels);
}
