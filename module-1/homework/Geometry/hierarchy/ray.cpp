#include "ray.h"

Ray::Ray(const Point &start, const Point &direction_point)
    : start_(start), direction_(Vector2(start, direction_point).normalized()) {}

Ray::Ray(const Point &start, const Vector2 &direction)
    : start_(start), direction_(direction.normalized()) {}

Vector2 Ray::getDirectionVector() const noexcept { return direction_; }

bool Ray::hasIntersection(const Segment &segment) {
  Point A = segment.getPointA();
  Point B = segment.getPointB();

  Line ray_line(start_,
                Point(start_.x + direction_.x, start_.y + direction_.y));
  Line segment_line(A, B);

  if (!ray_line.hasIntersection(segment_line)) {
    return false;
  }

  // There is intersection, it could be the whole line or one point
  if (ray_line == segment_line) {
    return common::gt(direction_ * Vector2(start_, A), 0) ||
           common::gt(direction_ * Vector2(start_, B), 0);
  }

  // There is intersection and it is just a one point
  double a1 = ray_line.a_, b1 = ray_line.b_, c1 = ray_line.c_;
  double a2 = segment_line.a_, b2 = segment_line.b_, c2 = segment_line.c_;
  double x = (c1 * b2 - b1 * c2) / (b1 * a2 - a1 * b2);
  double y = (a1 * c2 - c1 * a2) / (b1 * a2 - a1 * b2);

  return common::ge(direction_ * Vector2(start_, Point{x, y}), 0);
}
