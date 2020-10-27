
#include "ellipse.h"
#include "point.h"

class Circle: public Ellipse {
public:
  Circle(Point center, double radius);

  double radius() const noexcept;

private:
  Point& center_ = Ellipse::first_focus_;
  double& diameter_ = Ellipse::length_sum_;
};