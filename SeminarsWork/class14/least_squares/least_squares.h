#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H 1

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace lsm {

struct Point
{
  double x, y;

  Point() = default;

  Point(double xx, double yy) : x{xx}, y{yy}
  { /* empty body */
  }
};

std::istream& operator>> (std::istream& is, Point& rhs);
std::ostream& operator<< (std::ostream& os, const Point& rhs);

/** Read data of an experiment from file given as command
 *  line argument and having the following format:
 *  @note
 *    // some comment (may be omitted)
 *    (x1, y1)
 *    ...
 *    (xN, yN)
 */
std::vector<Point> read (const std::string& filename);

struct Coeffs
{
  double a, b;
};

/** For linear regression:
 *  @f[
 *      y = a + b*x
 *  @f]
 *  compute coefficients using the least squares method
 */
Coeffs least_squares (const std::vector<Point>& points);

}  // namespace lsm

#endif  // #ifndef LEAST_SQUARES_H
