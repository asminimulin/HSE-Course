#pragma once

#include "polygon.h"
#include <utility>
#include "line.h"

class Rectangle: public Polygon {
public:

  Rectangle() = default;

  Rectangle(const Point&A, const Point&B, double tangent);

  Point center() const noexcept;

  std::pair<Line, Line> getDiagonals() const noexcept;
};