#include "line.h"


bool Line::operator==(const Line &other) const {
    /*
     * a1x + b1y + c1 = 0
     * a2x + b2y + c2 = 0
     * a1 / a2 == b1 / b2 == c1 / c2
     */
    double a1 = this->a_, b1 = this->b_, c1 = this->c_;
    double a2 = other.a_, b2 = other.b_, c2 = other.c_;
    return a1 * b2 == a2 * b1 && a1 * c2 == a2 * c1 && b1 * c2 == b2 * c1;
}

bool Line::operator!=(const Line &other) const {
    return !(*this == other);
}

Line::Line(): a_(0), b_(0), c_(0) {}

/*
 *    x - a.x       y - a.y
 * ----------- ==  -----------
 *  a.x - b.x       a.y - b.y
 *
 *  (x - a.x) * (a.y - b.y) == (y - a.y) * (a.x - b.x)
 *  x * (a.y - b.y) + y * (b.x - a.x) + a.x * b.y - a.y * b.x = 0
 */
Line::Line(const Point &a, const Point &b): a_(a.y - b.y), b_(b.x - a.x), c_(a.x * b.y - a.y * b.x) {}
