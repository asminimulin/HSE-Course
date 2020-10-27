#pragma once

#include "rectangle.h"
#include "point.h"
#include "circle.h"

/**
 * @brief Square on Cartesian coordinate system
 */
class Square: public Rectangle {
public:

  /**
   * @brief Creates degenerate square
   */
  Square();

  /**
   * @brief Creates square with top left point at |top_left| and
   * bottom right point at |bottom_right|
   *
   * @param top_left Top left point
   * @param bottom_right Bottom right point
   */
  Square(Point top_left, Point bottom_right);

  /**
   * @brief Default copy constructor
   */
  Square(const Square&) = default;

  /**
   * @brief Default move constructor
   */
  Square(Square&&) = default;

  /**
   * @brief Creates circumscribed circle
   * @return Circumscribed circle
   */
  Circle circumscribedCircle() const noexcept;

  /**
   * @brief Creates inscribed circle
   * @return Inscribed circle
   */
  Circle inscribedCircle() const noexcept;

private:
  /**
   * @brief Size of square side
   */
  double size_;
};