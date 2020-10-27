#pragma once

/* It will use this Point implementation */
class Line;

/**
 * @brief Point in Cartesian coordinate system
 */
struct Point {

  /**
   * @brief Constructs a point at the (0, 0)
   */
  Point();

  /**
   * @brief Constructs a point at the (x, y)
   *
   * @param x X coordinate
   * @param y Y coordinate
   */
  Point(double x, double y);

  /**
   * @brief Constructs a point by copy semantics
   *
   * @param other The point needs to be copied
   */
  Point(const Point &other) = default;

  /**
   * @brief Constructs Point by move semantics
   *
   * @param other The point needs to be moved
   */
  Point(Point &&other) = default;

  /**
   * @brief Copies the provided point to this
   *
   * @param other The point needs to be copied
   * @return The reference to the current Point
   */
  Point &operator=(const Point &other) = default;

  /**
   * @brief Moved the provided point to this
   *
   * @param other The point needs to be moved
   * @return The reference to the current Point
   */
  Point &operator=(Point &&other) = default;

  /**
   * @brief Compares if this point is the same as other
   *
   * @param other The point needs to be compared to
   * @return True if the points are equal, False otherwise
   */
  bool operator==(const Point &other) const;

  /**
   * @brief Compares if this point is different from other
   *
   * @param other The point needs to be compared to
   * @return True if the points are not equal, False otherwise
   */
  bool operator!=(const Point &other) const;

  /**
   * @brief reflex point by axis
   */
  void reflex(const Line &axis);

  /**
   * @brief Reflexes copy of this point by center
   *
   * @param center Center of reflection
   *
   * @return Reflected copy of this point by center
   */
  Point reflected(const Point &center);

  bool lexicographically_less(const Point &other) const noexcept;

  /**
   * @brief rotates this point relatively provided point by angle
   *
   * @param point Point
   * @param angle Angle
   */
  void rotate(const Point &point, double angle) noexcept;

  /**
   * @brief Rotates copy of |this| point by |angle| angle relatively point
   * |center| and returns it
   * @param center Center of rotation
   * @param angle Rotation angle
   * @return Rotated copy
   */
  Point rotated(const Point &center, double angle) const noexcept;

  /**
   * @brief The value of coordinate on OX axis
   */
  double x;

  /**
   * @brief The value of coordinate on OY axis
   */
  double y;
};
