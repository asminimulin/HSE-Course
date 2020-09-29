#include "point.h"

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y): x(x), y(y) {}

bool Point::operator==(const Point &other) const {
    return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point &b) const {
    return !(*this == b);
}
