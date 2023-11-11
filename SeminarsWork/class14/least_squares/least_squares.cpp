#include <cmath>
#include <fstream>
#include <iterator>
#include <stdexcept>

#include "least_squares.h"

namespace lsm {

std::istream& operator>> (std::istream& is, Point& rhs)
{
  return is >> rhs.x >> rhs.y;
}

std::ostream& operator<< (std::ostream& os, const Point& rhs)
{
  return os << rhs.x << " " << rhs.y;
}

std::vector<Point> read (const std::string& filename)
{
  std::ifstream ifs{filename};
  if (!ifs)
    throw std::runtime_error{"can't open file '" + filename + "'"};

  return std::vector<Point>{std::istream_iterator<Point>{ifs},
                            std::istream_iterator<Point>{}};
}

Coeffs least_squares (const std::vector<Point>& points)
{
  // compute average values
  size_t N = points.size();
  double f_ave = 0., f2_ave = 0.;
  double y_ave = 0., fy_ave = 0.;

  for (const auto& p : points)
  {
    f_ave += p.x;
    f2_ave += p.x * p.x;
    y_ave += p.y;
    fy_ave += p.x * p.y;
  }
  f_ave /= N;
  f2_ave /= N;
  y_ave /= N;
  fy_ave /= N;

  // compute linear coefficient estimate
  double b = (fy_ave - f_ave * y_ave) / (f2_ave - f_ave * f_ave);

  if (!std::isfinite(b))
    throw std::overflow_error{"division by zero"};

  // compute constant coefficient estimate
  double a = y_ave - b * f_ave;

  return {a, b};
}

}  // namespace lsm
