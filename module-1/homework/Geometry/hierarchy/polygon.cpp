#include "polygon.h"

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <tuple>
#include <utility>

#include "common.hpp"
#include "ray.h"
#include "segment.h"

Polygon::Polygon(std::vector<Point> vertices) : vertices_(std::move(vertices)) {
  if (vertices_.size() < 3) {
    throw std::logic_error(
        "Cannot construct Polygon. At least 3 vertices required");
  }

  Normalize(vertices_);
}

Polygon::Polygon(const Polygon &other) : vertices_(other.vertices_) {}

Polygon::Polygon(Polygon &&other) noexcept
    : vertices_(std::move(other.vertices_)) {}

Polygon &Polygon::operator=(const Polygon &other) {
  vertices_ = other.vertices_;
  return *this;
}

Polygon &Polygon::operator=(Polygon &&other) noexcept {
  vertices_ = std::move(other.vertices_);
  return *this;
}

size_t Polygon::verticesCount() const noexcept { return vertices_.size(); }

std::vector<Point> Polygon::getVertices() const { return vertices_; }

/**
 * @details The polygon is convex when all points in walkthrough order
 * are by the same side of polygon edge.
 *
 * I go through all edges, represented by the edge a->b
 * and check if the next point c is by the positive side
 * of vector a->b or by the negative one.
 *
 * Finally I check that there are no points by the different side
 */
bool Polygon::isConvex() const {
  bool positive = false;
  bool negative = false;

  /**
   * Trying to avoid if statements inside this for loop,
   * because it has more chances to vectorize this operations
   */
  for (size_t pos = 0; pos < vertices_.size(); ++pos) {
    auto next = (pos + 1) % vertices_.size();
    auto next2 = (pos + 2) % vertices_.size();

    auto a = vertices_[pos];
    auto b = vertices_[next];
    auto c = vertices_[next2];

    auto vector_production = (Vector2(a, b) ^ Vector2(a, c));
    positive |= common::gt(vector_production, 0);
    negative |= common::lt(vector_production, 0);
  }

  return !(positive && negative);
}

double Polygon::perimeter() noexcept {
  double result = 0;

  for (auto i = 0; i < vertices_.size(); ++i) {
    auto next = (i + 1) % vertices_.size();
    result += common::dist(vertices_[i], vertices_[next]);
  }

  return result;
}

double Polygon::area() noexcept {
  double result = 0;
  auto basePoint = vertices_.front();

  for (auto i = 1; i + 1 < vertices_.size(); ++i) {
    auto vec1 = Vector2(basePoint, vertices_[i]);
    auto vec2 = Vector2(basePoint, vertices_[i + 1]);
    result += (vec1 ^ vec2);
  }

  return std::abs(result / 2);
}

bool Polygon::operator==(const Shape &other) const noexcept {
  auto other_polygon = dynamic_cast<const Polygon *>(&other);
  if (other_polygon == nullptr) {
    // other is not even a polygon
    return false;
  }

  return vertices_ == other_polygon->vertices_;
}

bool Polygon::isCongruentTo(const Shape &other) const noexcept {
  auto other_polygon = dynamic_cast<const Polygon *>(&other);
  if (other_polygon == nullptr) {
    // other is not event a polygon
    return false;
  }

  if (vertices_.size() != other_polygon->vertices_.size()) {
    return false;
  }

  for (auto cur = 0; cur < vertices_.size(); ++cur) {
    auto previous = (vertices_.size() + cur - 1) % vertices_.size();
    auto next = (cur + 1) % vertices_.size();

    auto this_A = vertices_[previous];
    auto this_O = vertices_[cur];
    auto this_B = vertices_[next];

    auto other_A = other_polygon->vertices_[previous];
    auto other_O = other_polygon->vertices_[cur];
    auto other_B = other_polygon->vertices_[next];

    auto this_length = common::dist(this_O, this_B);
    auto other_length = common::dist(other_O, other_B);

    if (common::ne(this_length, other_length)) {
      return false;
    }

    auto this_angle =
        Vector2::getAngle(Vector2(this_O, this_A), Vector2(this_O, this_B));
    auto other_angle =
        Vector2::getAngle(Vector2(other_O, other_A), Vector2(other_O, other_B));

    if (common::ne(this_angle, other_angle)) {
      return false;
    }
  }

  return true;
}

bool Polygon::isSimilarTo(const Shape &other) const noexcept {
  auto other_polygon = dynamic_cast<const Polygon *>(&other);
  if (other_polygon == nullptr) {
    // other is not event a polygon
    return false;
  }

  if (vertices_.size() != other_polygon->vertices_.size()) {
    return false;
  }

  for (auto cur = 0; cur < vertices_.size(); ++cur) {
    auto previous = (vertices_.size() + cur - 1) % vertices_.size();
    auto next = (cur + 1) % vertices_.size();

    auto this_A = vertices_[previous];
    auto this_O = vertices_[cur];
    auto this_B = vertices_[next];

    auto other_A = other_polygon->vertices_[previous];
    auto other_O = other_polygon->vertices_[cur];
    auto other_B = other_polygon->vertices_[next];

    auto this_angle =
        Vector2::getAngle(Vector2(this_O, this_A), Vector2(this_O, this_B));
    auto other_angle =
        Vector2::getAngle(Vector2(other_O, other_A), Vector2(other_O, other_B));

    if (common::ne(this_angle, other_angle)) {
      return false;
    }
  }

  return true;
}

bool Polygon::containsPoint(Point point) const noexcept {
  // fixme: add random point choice
  Ray ray(point, Vector2{242423234.0, 23423842.0});

  bool is_inside = false;

  for (auto i = 0; i < vertices_.size(); ++i) {
    auto A = vertices_[i];
    auto B = vertices_[(i + 1) % vertices_.size()];

    if (ray.hasIntersection(Segment{A, B})) {
      is_inside ^= true;
    }
  }
  return is_inside;
}

void Polygon::rotate(Point center, double angle) noexcept {
  angle = common::DegreesToRadians(angle);

  for (auto &point : vertices_) {
    auto x_centerized = point.x - center.x;
    auto y_centerized = point.y - center.y;
    auto new_x = center.x + (std::cos(angle) * x_centerized -
                             std::sin(angle) * y_centerized);
    auto new_y = center.y + (std::sin(angle) * x_centerized +
                             std::cos(angle) * y_centerized);
    point = {new_x, new_y};
  }

  Normalize(vertices_);
}

void Polygon::reflex(Point center) noexcept {
  for (auto &point : vertices_) {
    auto move = Vector2(point, center);
    move *= 2;
    point = {point.x + move.getX(), point.y + move.getY()};
  }
  Normalize(vertices_);
}

void Polygon::reflex(Line line) noexcept {
  Point A, B;
  std::tie(A, B) = line.Get2Points();
  for (auto &point : vertices_) {

    // Get Q
    Vector2 pa(point, A);
    Vector2 pb(point, B);
    Vector2 ab(A, B);

    auto PQ_length = std::abs(pa ^ pb) / ab.length();

    // Try one direction
    auto pq = ab.rotated(common::PI / 2) * (PQ_length / ab.length());
    Point Q(point.x + pq.getX(), point.y + pq.getY());
    auto result = point.reflected(Q);

    if (common::gt(ab ^ Vector2(A, result), 0) ==
        common::gt(ab ^ Vector2(A, point), 0)) {
      pq *= -1;
      Q = {point.x + pq.getX(), point.y + pq.getY()};
      result = point.reflected(Q);
    }

    point = result;
  }
  Normalize(vertices_);
}

void Polygon::scale(Point center, double coefficient) noexcept {
  for (auto &point : vertices_) {
    auto new_x = coefficient * point.x + (1 - coefficient) * center.x;
    auto new_y = coefficient * point.y + (1 - coefficient) * center.y;
    point = {new_x, new_y};
  }
  Normalize(vertices_);
}

void Polygon::Normalize(std::vector<Point> &vertices) noexcept {

  auto lexicographical_less = [](const Point &a, const Point &b) {
    return common::lt(a.x, b.x) ||
           (common::eq(a.x, b.x) && common::lt(a.y, b.y));
  };

  auto min_vertex_it =
      std::min_element(vertices.begin(), vertices.end(), lexicographical_less);

  if (min_vertex_it != vertices.begin()) {
    // Move subarray to the end of vector
    std::rotate(vertices.begin(), min_vertex_it, vertices.end());

    auto right = *++vertices.begin(); //< right by the vertices_.front()
    auto left = vertices.back();      //< left by the vertices_.front()

    if (common::lt(left.y, right.y) ||
        (common::eq(left.y, right.y) && common::lt(left.x, right.x))) {
      std::reverse(++vertices.begin(), vertices.end());
    }
  }
}
