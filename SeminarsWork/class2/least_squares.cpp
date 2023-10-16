#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
    double x, y;

    Point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) {}
};

istream& operator>> (istream& is, Point& p)
{
    is >> p.x >> p.y;
    return is;
}

int main (void)
{
    ifstream fin("SeminarsWork/class2/input.txt");
    Point p;
    vector<Point> v;
    while (fin >> p)
        v.push_back(p);
    double average_y = 0.0, average_x = 0.0, average_xy = 0.0, average_x_square = 0.0;
    for (size_t i = 0; i < v.size(); i++)
    {
        average_y += v[i].y;
        average_x += v[i].x;
        average_xy += v[i].x * v[i].y;
        average_x_square += v[i].x * v[i].x;
    }
    average_y /= v.size();
    average_x /= v.size();
    average_xy /= v.size();
    average_x_square /= v.size();
    double a, b;
    b = (average_xy - average_x * average_y) / (average_x_square - average_x * average_x);
    a = average_y - b * average_x;
    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}