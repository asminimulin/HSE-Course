#pragma once

#include "line.h"
#include "point.h"

class Shape {
public:
  virtual double perimeter() = 0;

  virtual double area() = 0;

  virtual bool operator==(const Shape &other) const = 0;

  virtual bool isCongruentTo(const Shape &other) const = 0;

  virtual bool isSimilarTo(const Shape &other) const = 0;

  virtual bool containsPoint(Point point) const = 0;

  virtual void rotate(Point center, double angle) = 0;

  virtual void reflex(Point center) = 0;

  virtual void reflex(Line axis) = 0;

  virtual void scale(Point center, double coefficient) = 0;

  virtual ~Shape() = default;
};