#pragma once

#include "shape.h"

/**
 * @brief Ellipse on the Cartesian coordinate system
 */
class Ellipse : public Shape {
public:
  /**
   * @brief Creates default degenerate ellipse
   */
  Ellipse() noexcept = default;

  /**
   * @brief Creates ellipse with focuses at the points first_focus and
   * second_focus with length sum equal to length_sum_
   *
   * @param first_focus First focus
   * @param second_focus Second focus
   * @param length_sum Length sum
   */
  Ellipse(const Point &first_focus, const Point &second_focus,
          double length_sum);

  /**
   * @brief Gets focuses of ellipse
   *
   * @return Two points: ellipse's focuses
   */
  std::pair<Point, Point> focuses() const noexcept;

  /**
   * @brief Gets directrices of ellipse
   *
   * @return Two lines: directrices of ellipse
   */
  std::pair<Line, Line> directrices() const noexcept;

  /**
   * @brief Gets ellipse eccentricity
   *
   * @return Eccentricity of ellipse
   */
  double eccentricity() const noexcept;

  /**
   * @brief Returns center of the ellipse
   *
   * @return Point - center of the ellipse
   */
  Point center() const noexcept;

  double majorSemiAxis() const noexcept;

  double minorSemiAxis() const noexcept;

  double perimeter() noexcept override;

  double area() noexcept override;

  bool operator==(const Shape& other) const noexcept override;

  bool isCongruentTo(const Shape& other) const noexcept override;

  bool isSimilarTo(const Shape& other) const noexcept override;

  bool containsPoint(Point point) const noexcept override;

  void rotate(Point center, double angle) noexcept override;

  void reflex(Point center) noexcept override;

  void reflex(Line axis) noexcept override;

  void scale(Point center, double coefficient) noexcept override;

protected:
  /**
   * @brief First focus
   */
  Point first_focus_;

  /**
   * @brief Second focus
   */
  Point second_focus_;

  /**
   * @brief Length sum
   */
  double length_sum_;
};