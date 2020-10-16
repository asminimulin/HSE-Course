#pragma once

#include "point.h"
#include "polygon.h"

class Triangle: public Polygon {
public:
  explicit Triangle(Point a, Point b, Point c);
};