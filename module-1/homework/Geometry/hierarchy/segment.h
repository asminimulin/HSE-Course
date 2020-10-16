#pragma once

#include "point.h"


/**
 * @brief Segment class
 */
class Segment {
public:
  /**
   * @brief Creates degenerate segment
   */
  Segment() = default;

  /**
   * @brief Creates segment with edge points a and b
   *
   * @param a Point A
   * @param b Point B
   */
  Segment(const Point& a, const Point& b) noexcept: a_(a), b_(b) {}

  /**
   * @brief Getter for edge point A
   *
   * @return Point A
   */
  inline Point getPointA() const noexcept { return a_; }

  /**
   * @brief Getter for edge point B
   *
   * @return Point B
   */
  inline Point getPointB() const noexcept { return b_; }

private:
  /**
   * @brief Edge point A
   */
  Point a_;

  /**
   * @brief Edge point B
   */
  Point b_;
};