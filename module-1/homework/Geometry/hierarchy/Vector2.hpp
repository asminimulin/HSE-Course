//
// Created by aminimulin on 29.09.2020.
//

#pragma once

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
    inline Vector2(): x(0), y(0) {}

    /**
     * @brief Construct a vector from (0, 0) to (x_, y_)
     *
     * @param x_ X coordinate
     * @param y_ Y coordinate
     */
    inline Vector2(double x_, double y_): x(x_), y(y_) {}

    /**
     * @brief Constructs a vector from point a to point b
     *
     * @param a
     * @param b
     */
    inline explicit Vector2(Point a, Point b): x(b.x- a .x), y(b.y - a.y) {}

    /**
     * @brief Scalar production
     *
     * @param other Second vector
     * @return Value of scalar production
     */
    inline double operator*(const Vector2& other) const noexcept {
        return this->x * other.x + this->y * other.y;
    }

    /**
     * @brief vector production
     *
     * @param other
     * @return Value of vector production
     */
    inline double operator^(const Vector2& other) const noexcept {
        return this->x * other.y - this->y * other.x;
    }

    /**
     * @brief Value of coordinate on OX axis
     */
    double x;

    /**
     * @brief Value of coordinate on OY axis
     */
    double y;
};
