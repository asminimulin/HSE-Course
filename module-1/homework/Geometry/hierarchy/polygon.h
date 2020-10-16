#pragma once

#include <cstddef>
#include <vector>

#include "Vector2.hpp"
#include "point.h"
#include "shape.h"

/**
 * @brief Polygon on the Cartesian coordinate system
 */
class Polygon : public Shape {
public:
  /**
   * @brief Constructs polygon with provided vertices
   *
   * It does not check that polygon has no self-intersections,
   * the caller code should care of it
   *
   * @param vertices The vertices
   */
  explicit Polygon(std::vector<Point> vertices);

  /**
   * @brief Constructs polygon by moving other
   *
   * @param other The other polygon
   *
   * @throw std::bad_alloc() if failed to allocate memory for containing
   * vertices
   */
  Polygon(const Polygon &other);

  /**
   * @brief Constructs polygon by moving other
   *
   * @param other The other polygon
   */
  Polygon(Polygon &&other) noexcept;

  /**
   * @brief Copies the other polygon to this
   *
   * @param other The other polygon
   *
   * @return Reference to this polygon
   *
   * @throw std::bad_alloc() if failed to allocate memory for containing
   * vertices
   */
  Polygon &operator=(const Polygon &other);

  /**
   * @brief Moves the other polygon to this
   *
   * @param other The other polygon
   *
   * @return Reference to this polygon
   */
  Polygon &operator=(Polygon &&other) noexcept;

  /**
   * @brief The vertices count
   *
   * @return The vertices count
   */
  size_t verticesCount() const noexcept;

  /**
   * @brief Polygon's vertices
   *
   * @return Copied vertices
   *
   * @throw std::bad_alloc() if failed to allocate memory for vertices
   */
  std::vector<Point> getVertices() const;

  /**
   * @brief Check if the polygon is convex
   *
   * @return True if polygon is convex, false otherwise
   */
  bool isConvex() const;

  /**
   * @brief The perimeter of polygon
   *
   * @return The perimeter of polygon
   */
  double perimeter() noexcept override;

  /**
   * @brief The area of polygon
   *
   * @return The area of polygon
   */
  double area() noexcept override;

  /**
   * @brief Check if this Polygon is equal ot Shape other
   *
   * @param other Shape other
   *
   * @return True if this polygon is equal to Shape other, false otherwise
   */
  bool operator==(const Shape &other) const noexcept override;

  /**
   * @brief Check if this polygon is congruent to Shape other
   *
   * @param other Shape other
   *
   * @return True if this polygon is congruent to Shape other, false otherwise
   */
  bool isCongruentTo(const Shape &other) const noexcept override;

  /**
   * @brief Check if this polygon is similar to Shape other
   *
   * @param other Other shape
   *
   * @return True if this polygon is similar to Shape other, false otherwise
   */
  bool isSimilarTo(const Shape &other) const noexcept override;

  /**
   * @brief Check if point is inside this polygon
   *
   * @param point The point needs to be checked
   *
   * @return True if point is inside this polygon
   */
  bool containsPoint(Point point) const noexcept override;

  /**
   * @brief Rotate polygon relatively to Point center by angle(in degrees)
   *
   * @param center Center of rotation
   *
   * @param angle Angle the rotation applying by
   */
  void rotate(Point center, double angle) noexcept override;

  /**
   * @brief Reflex polygon relatively the center
   *
   * @param center Point by which reflection is applied
   */
  void reflex(Point center) noexcept override;

  /**
   * @brief Reflex polygon relatively the line
   *
   * @param line Line by which reflection is applied
   */
  void reflex(Line line) noexcept override;

  /**
   * @brief Scale polygon
   *
   * @param center Center of scale
   *
   * @param coefficient Coefficient of scale
   */
  void scale(Point center, double coefficient) noexcept override;

  /**
   * @brief Destructor
   */
  ~Polygon() noexcept override = default;

protected:
  /**
   * @brief Normalize internal points representation
   *
   * It implements vertices reordering to support this invariant:
   * 1) first vertex is the most left and the lowest among the most left.
   * 2) The second vertex is the vertex which should the next right after first
   *    in counter clockwise (a.k.a mathematically positive) order
   *
   * @param vertices
   */
  static void Normalize(std::vector<Point> &vertices) noexcept;

  /**
   * @brief Protected constructor for usage in children who extends Polygon
   * interface
   */
  Polygon() = default;

  /**
   * @brief Polygon's vertices.
   *
   * @details It is assumed that first Point is lexicographically minimal
   */
  std::vector<Point> vertices_;
};