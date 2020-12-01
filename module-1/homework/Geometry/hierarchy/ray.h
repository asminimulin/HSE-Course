#pragma once

#include "Vector2.hpp"
#include "line.h"
#include "segment.h"

/**
 * @brief Ray class
 */
class Ray {
public:
  /**
   * @brief Creates degenerated instance of ray
   */
  Ray() = default;

  /**
   * @brief Creates Ray that:
   * 1) begins at the point start
   * 2) directed to the point direction_point
   * @param start Beginning of the ray
   * @param direction_point Point that set direction of the ray
   */
  Ray(const Point &start, const Point &direction_point);

  /**
   * @brief Creates Ray that:
   * 1) begins at point start
   * 2) co-directed with vector direction
   * @param start Beginning of the ray
   * @param direction Direction of the ray
   */
  Ray(const Point &start, const Vector2 &direction);

  /**
   * @brief Returns normalized vector that is co-directed with the ray
   * @return Normalized vector that is co-directed with the ray
   */
  Vector2 getDirectionVector() const noexcept;

  /**
   * @brief Checks if ray intersects with segment
   * @param segment Segment
   * @return True if ray intersects with segment
   */
  bool hasIntersection(const Segment& segment);

protected:
  /**
   * @brief start of the vector
   */
  Point start_;
  Vector2 direction_;
};
