#pragma once

#include "ellipse.h"
#include "point.h"

class Circle: public Ellipse {
 public:

  /**
   * @brief Creates default circle which could be unsafe to be used until
   * assign any valid circle
   */
  Circle() = default;

  /**
   * @brief Constructs safe and valid circle
   * @param center Center of the circle
   * @param radius Radius of the circle
   */
  Circle(Point center, double radius);

  /**
   * @brief Returns radius of |this| circle
   * @return Radius
   */
  double radius() const noexcept;

private:
  Point& center_ = Ellipse::first_focus_;
  double& diameter_ = Ellipse::length_sum_;
};