//
// Created by aminimulin on 29.09.2020.
//

#pragma once

#include <cmath>

#include "common.hpp"
#include "point.h"

/**
 * @brief 2-dimensional in Cartesian coordinates
 *
 * The vector's beginning is the start of Cartesian coordinate system.
 * Use inline implementation to achieve the max performance. It is necessary
 * because it is used for actual mathematical calculations.
 */
struct Vector2 {
  /**
   * @brief Construct a null vector
   */
  inline Vector2() : x(0), y(0) {}

  /**
   * @brief Construct a vector from (0, 0) to (x_, y_)
   *
   * @param x_ X coordinate
   * @param y_ Y coordinate
   */
  inline Vector2(double x_, double y_) : x(x_), y(y_) {}

  /**
   * @brief Constructs a vector from point a to point b
   *
   * @param a
   * @param b
   */
  inline explicit Vector2(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}

  /**
   * @brief Scalar production
   *
   * @param other Second vector
   *
   * @return Value of scalar production
   */
  inline double operator*(const Vector2& other) const noexcept {
    return this->x * other.x + this->y * other.y;
  }

  /**
   * @brief Multiplies vector by factor
   *
   * @param factor
   *
   * @return Result vector
   */
  inline Vector2& operator*=(double factor) {
    x *= factor;
    y *= factor;
    return *this;
  }

  /**
   * @brief Multiplies copy of this vector by factor
   *
   * @return Copy of this vector multiplied by factor
   */
  inline Vector2 operator*(double factor) const noexcept {
    return Vector2{x * factor, y * factor};
  }

  /**
   * @brief vector production
   *
   * @param other
   *
   * @return Value of vector production
   */
  inline double operator^(const Vector2& other) const noexcept {
    return this->x * other.y - this->y * other.x;
  }

  /**
   * @brief Calculates angle between vectors a and b
   *
   * @param a Vector a
   * @param b Vector b
   *
   * @return Angle between vectors
   */
  static inline double getAngle(const Vector2& a, const Vector2& b) noexcept {
    auto scalar_production = a * b;
    if (common::ne(scalar_production, 0)) {
      return std::acos(scalar_production / (a.length() * b.length()));
    } else {
      return std::asin((a ^ b) / (a.length() * b.length()));
    }
  }

  /**
   * @brief Calculates length of vector
   * @return Length of vector
   */
  inline double length() const noexcept { return std::sqrt(x * x + y * y); }

  inline void normalize() noexcept {
    auto length_ = length();
    x /= length_;
    y /= length_;
  }

  /**
   * @brief Normalizes copy of this vector
   *
   * @return Normalized copy of this vector
   */
  inline Vector2 normalized() const noexcept {
    auto result = *this;
    result.normalize();
    return result;
  }

  /**
   * @brief Rotates this vector by angle
   *
   * @param angle Angle in radians
   */
  inline void rotate(const double angle) noexcept {
    auto new_x = std::cos(angle) * x - std::sin(angle) * y;
    y = std::sin(angle) * x + std::cos(angle) * y;
    x = new_x;
  }

  /**
   * @brief Rotates copy of this vector by angle
   *
   * @param angle Angle in radians
   *
   * @return Copy of this vector rotated by angle
   */
  inline Vector2 rotated(const double angle) const noexcept {
    auto result = *this;
    result.rotate(angle);
    return result;
  }

  /**
   * @brief Getter for X coordinate
   *
   * @return X coordinate of vector
   */
  inline double getX() const noexcept {
    return x;
  }

  /**
   * @brief Getter for Y coordinate
   *
   * @return Y coordinate of vector
   */
  inline double getY() const noexcept {
    return y;
  }

 private:
  /**
   * @brief Value of coordinate on OX axis
   */
  double x;

  /**
   * @brief Value of coordinate on OY axis
   */
  double y;
};
