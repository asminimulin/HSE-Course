#include "point.h"
#include "Vector2.hpp"
#include "common.hpp"
#include "line.h"

#include <tuple>

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

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

bool Point::lexicographically_less(const Point &other) const noexcept {
  return common::lt(x, other.x) ||
         (common::eq(x, other.x) && common::lt(y, other.y));
}

void Point::rotate(const Point &point, double angle) noexcept {
  auto new_x = std::cos(angle) * x - std::sin(angle) * y;
  y = std::sin(angle) * x + std::sin(angle) * y;
  x = new_x;
}

void Point::reflex(const Line &axis) {
  Point A, B;
  std::tie(A, B) = axis.Get2Points();

  auto n_length =
      std::abs(Vector2(*this, A) ^ Vector2(*this, B)) / common::dist(A, B);

  auto n = Vector2(A, B).rotated(common::PI / 2) * n_length;

  Point Q(x + n.x, y + n.y);

  Point result = rotated(Q);

  Vector2 ab(A, B);
  if (common::gt(ab ^ Vector2(A, result), 0),
      common::gt(ab ^ Vector2(A, *this), 0)) {
    Q = {x - n.x, y - n.y};
    result = rotated(Q);
  }

  *this = result;
}

Point Point::rotated(const Point &center) const noexcept {
  auto result = *this;
  result.rotated(center);
  return result;
}
