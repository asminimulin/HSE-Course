#include "rectangle.h"

/**
 * @todo: add mathematics explanation with pictures
 */
Rectangle::Rectangle(const Point &A, const Point &B, double tangent) {
  Vector2 ab(A, B);

  auto AH_div_HB = 1 / (tangent * tangent);

  auto AH_length = ab.length() * (AH_div_HB / (1 + AH_div_HB));

  auto ah = ab.normalized() * AH_length;

  Point H(A.x + ah.getX(), A.y + ah.getY());

  auto CH_length = std::sqrt((ab.length() - AH_length) * AH_length);

  Vector2 hc = ah.rotated(common::PI / 2) * (CH_length / ah.length());
  Point C(H.x + hc.getX(), H.y + hc.getY());

  Vector2 kd = hc * -1;
  Point K(A.x + (ab.getX() - ah.getX()), A.y + (ab.getY() - ah.getY()));
  Point D(K.x + kd.getX(), K.y + kd.getY());

  Polygon::vertices_ = {A, C, B, D};

  Normalize(Polygon::vertices_);
}

Point Rectangle::center() const noexcept {
  const Point& A = Polygon::vertices_[0];
  const Point& B = Polygon::vertices_[2];

  auto ab_half = Vector2(A, B) * 0.5;
  return Point{A.x + ab_half.getX(), A.y + ab_half.getY()};
}

std::pair<Line, Line> Rectangle::getDiagonals() const noexcept {
  Line first(Polygon::vertices_[0], Polygon::vertices_[2]);
  Line second(Polygon::vertices_[1], Polygon::vertices_[3]);
  return {first, second};
}
