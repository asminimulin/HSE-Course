#pragma once
#include "point.h"
#include <utility>

class Line {
  friend class Ray;

public:
  Line();
  Line(const Point &a, const Point &b);

  bool operator==(const Line &other) const;
  bool operator!=(const Line &other) const;

  std::pair<Point, Point> Get2Points() const noexcept;

  bool hasIntersection(const Line& line) const noexcept;

private:
  double a_, b_, c_;
};
