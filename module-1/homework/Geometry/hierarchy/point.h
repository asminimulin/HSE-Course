#pragma once

struct Point {
    Point();

    Point(double x, double y);

    Point(const Point &other) = default;

    Point(Point &&other) = default;

    Point &operator=(const Point &other) = default;

    Point &operator=(Point &&other) = default;

    bool operator==(const Point &other) const;

    bool operator!=(const Point &b) const;


    double x;
    double y;
};
