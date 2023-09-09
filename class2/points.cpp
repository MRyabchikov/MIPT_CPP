#include <iostream>
#include <vector>
using namespace std;

struct Point
{
  double x, y;
};

int main (void)
{
  Point p = {4, 5};
  vector<Point> points;
  points.push_back(p);

  return 0;
}