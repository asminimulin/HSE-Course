
#include "square.h"
#include "Vector2.hpp"
#include <cmath>

Square::Square(Point top_left, Point bottom_right)
    : Rectangle(top_left, bottom_right, 1.0) {
  size_ = common::dist(top_left, bottom_right) / std::sqrt(2);
}

Circle Square::circumscribedCircle() const noexcept {
  auto center = this->center();
  auto radius = size_ / std::sqrt(2);
  return Circle(center, radius);
}

Circle Square::inscribedCircle() const noexcept {
  auto center = this->center();
  auto radius = size_ / 2;
  return Circle(center, radius);
}

Square::Square(): size_(0) {}
