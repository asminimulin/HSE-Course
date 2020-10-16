#include "point.h"
#include "common.hpp"
#include "Vector2.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y): x(x), y(y) {}

bool Point::operator==(const Point &other) const {
    return common::eq(this->x, other.x) && common::eq(this->y, other.y);
}

bool Point::operator!=(const Point &other) const {
  return common::ne(this->x, other.x) || common::ne(this->y, other.y);
}

Point Point::reflected(const Point &center) {
  Vector2 vec(*this, center);
  vec *= 2;
  return Point{x + vec.x, y + vec.y};
}
