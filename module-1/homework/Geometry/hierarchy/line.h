#pragma once
#include "point.h"

class Line {
public:
    Line();
    Line(const Point& a, const Point& b);

    bool operator==(const Line& other) const;
    bool operator!=(const Line& other) const;

private:
    double a_, b_, c_;
};
