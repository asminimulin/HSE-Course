#include "line.h"
#include "common.hpp"

/**
 * @details I do not use division because I do not want to think about
 * any coefficient that could be zeroed
 */
bool Line::operator==(const Line &other) const {
  /*
   * a1x + b1y + c1 = 0
   * a2x + b2y + c2 = 0
   * a1 / a2 == b1 / b2 == c1 / c2
   */
  double a1 = this->a_, b1 = this->b_, c1 = this->c_;
  double a2 = other.a_, b2 = other.b_, c2 = other.c_;
  return a1 * b2 == a2 * b1 && a1 * c2 == a2 * c1 && b1 * c2 == b2 * c1;
}

bool Line::operator!=(const Line &other) const { return !(*this == other); }

Line::Line() : a_(0), b_(0), c_(0) {}

/*
 *    x - a.x       y - a.y
 * ----------- ==  -----------
 *  a.x - b.x       a.y - b.y
 *
 *  (x - a.x) * (a.y - b.y) == (y - a.y) * (a.x - b.x)
 *  x * (a.y - b.y) + y * (b.x - a.x) + a.x * b.y - a.y * b.x = 0
 */
Line::Line(const Point &a, const Point &b)
    : a_(a.y - b.y), b_(b.x - a.x), c_(a.x * b.y - a.y * b.x) {}

std::pair<Point, Point> Line::Get2Points() const noexcept {
  if (common::ne(a_, 0)) {

    double y = 10;
    Point A((-c_ - b_ * y) / a_, y);
    y = 20;
    Point B((-c_ - b_ * y) / a_, y);
    return {A, B};

  } else {

    double x = 10;
    Point A(x, (-c_ - a_ * x) / b_);
    x = 20;
    Point B(x, (-c_ - a_ * x) / b_);
    return {A, B};
  }
}

/**
 * @details I do not use divisions because I do not want to check if
 * any coefficient is equal to zero
 */
bool Line::hasIntersection(const Line &line) const noexcept {

  bool is_parallel = common::eq(a_ * line.b_, b_ * line.a_) &&
    common::eq(b_ * line.c_, c_ * line.b_) &&
    common::eq(c_ * line.a_, a_ * line.c_);

  if (is_parallel) {
    return common::eq(c_, line.c_);
  }

  return true;
}
