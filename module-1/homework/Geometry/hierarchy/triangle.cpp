#include "triangle.h"

Triangle::Triangle(Point a, Point b, Point c)
    : Polygon(std::vector<Point>{a, b, c}) {}
