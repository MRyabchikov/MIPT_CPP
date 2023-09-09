#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main (void)
{
  double x, y;
  vector<pair<int, int>> v;
  while (cin >> x >> y)
    v.push_back(make_pair(x, y));
  double average_y = 0.0, average_x = 0.0, average_xy = 0.0,
         average_x_square = 0.0;
  for (size_t i = 0; i < v.size(); i++)
  {
    average_y += v[i].second;
    average_x += v[i].first;
    average_xy += v[i].first * v[i].second;
    average_x_square += v[i].first * v[i].first;
  }
  average_y /= v.size();
  average_x /= v.size();
  average_xy /= v.size();
  average_x_square /= v.size();
  double a, b;
  b = (average_xy - average_x * average_y) /
      (average_x_square - average_x * average_x);
  a = average_y - b * average_x;
  cout << "a = " << a << ", b = " << b << endl;
  return 0;
}