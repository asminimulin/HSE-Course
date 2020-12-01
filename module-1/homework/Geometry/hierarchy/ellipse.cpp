#include "ellipse.h"
#include "Vector2.hpp"
#include <tuple>
#include <utility>

Ellipse::Ellipse(const Point &first_focus, const Point &second_focus,
                 double length_sum)
    : first_focus_(first_focus), second_focus_(second_focus),
      length_sum_(length_sum) {
  if (second_focus_.lexicographically_less(first_focus_)) {
    std::swap(first_focus_, second_focus_);
  }
}

std::pair<Point, Point> Ellipse::focuses() const noexcept {
  return {first_focus_, second_focus_};
}

std::pair<Line, Line> Ellipse::directrices() const noexcept {
  auto n =
      Vector2(first_focus_, second_focus_).normalized().rotated(common::PI / 2);

  Point S1(first_focus_.x + n.getX(), first_focus_.y + n.getY());
  Point S2(first_focus_.x - n.getX(), first_focus_.y - n.getY());

  Point T1(second_focus_.x + n.getX(), first_focus_.y + n.getY());
  Point T2(second_focus_.x - n.getX(), second_focus_.y - n.getY());

  return {Line(S1, S2), Line(T1, T2)};
}

double Ellipse::eccentricity() const noexcept {
  return (Vector2(first_focus_, second_focus_).length()) / (length_sum_);
}

Point Ellipse::center() const noexcept {
  Vector2 vec(first_focus_, second_focus_);
  vec *= 0.5;
  return {first_focus_.x + vec.getX(), first_focus_.y + vec.getY()};
}

double Ellipse::majorSemiAxis() const noexcept { return length_sum_ / 2; }

double Ellipse::minorSemiAxis() const noexcept {
  auto a = majorSemiAxis();

  /**
   * @note Use scalar production because it is has better precision and
   * performance
   */
  auto vec = Vector2(first_focus_, second_focus_) * 0.5;
  return sqrt(a * a - vec * vec);
}

double Ellipse::perimeter() noexcept {
  auto a = majorSemiAxis();
  auto b = minorSemiAxis();
  return 4 * (common::PI * a * b + (a - b)) / (a + b);
}

double Ellipse::area() noexcept {
  auto a = majorSemiAxis();
  auto b = minorSemiAxis();
  return common::PI * a * b;
}

bool Ellipse::operator==(const Shape &other) const noexcept {
  auto other_ellipse = dynamic_cast<const Ellipse *>(&other);

  if (other_ellipse == nullptr) {
    // Other is not even an ellipse
    return false;
  }

  return first_focus_ == other_ellipse->first_focus_ &&
         second_focus_ == other_ellipse->second_focus_ &&
         common::eq(length_sum_, other_ellipse->length_sum_);
}

bool Ellipse::isCongruentTo(const Shape &other) const noexcept {
  auto other_ellipse = dynamic_cast<const Ellipse *>(&other);

  if (other_ellipse == nullptr) {
    // Other shape is not even an ellipse
    return false;
  }

  return common::eq(length_sum_, other_ellipse->length_sum_) &&
         common::eq(common::dist(first_focus_, second_focus_),
                    common::dist(other_ellipse->first_focus_,
                                 other_ellipse->second_focus_));
}

bool Ellipse::isSimilarTo(const Shape &other) const noexcept {
  auto other_ellipse = dynamic_cast<const Ellipse*>(&other);

  if (other_ellipse == nullptr) {
    // not even an ellipse
    return false;
  }
  return common::eq(this->majorSemiAxis() * other_ellipse->minorSemiAxis(),
                    this->minorSemiAxis() * other_ellipse->majorSemiAxis());
}

bool Ellipse::containsPoint(Point point) const noexcept {
  return common::le(common::dist(first_focus_, point) +
                        common::dist(second_focus_, point),
                    length_sum_);
}

void Ellipse::rotate(Point center, double angle) noexcept {
  first_focus_.rotate(center, common::DegreesToRadians(angle));
  second_focus_.rotate(center, common::DegreesToRadians(angle));
}

void Ellipse::reflex(Point center) noexcept {
  first_focus_ = first_focus_.reflected(center);
  second_focus_ = second_focus_.reflected(center);
}

void Ellipse::reflex(Line axis) noexcept {
  first_focus_.reflex(axis);
  second_focus_.reflex(axis);
}

void Ellipse::scale(Point center, double coefficient) noexcept {
  for (Point* p_ptr : {&first_focus_, &second_focus_}) {
    Point& p = *p_ptr;
    auto x = (p.x - center.x) * coefficient + center.x;
    auto y = (p.y - center.y) * coefficient + center.y;
    p.x = x;
    p.y = y;
  }
//  length_sum_ *= coefficient * coefficient;
  length_sum_ *= coefficient;
}
