//
// Created by aminimulin on 14.10.2020.
//

#ifndef GEOMETRY_COMMON_HPP
#define GEOMETRY_COMMON_HPP

#include "point.h"

#include <cmath>

namespace common {

const double EPSILON = 1e-6;
const double PI = 3.1415926;


/**
 * @brief Calculates distance between two points
 * @param a Point a
 * @param b Point b
 * @return Distance between points a and b
 */
inline double dist(const Point& a, const Point& b) noexcept {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


/**
 * @brief Check if a less than b
 * @param a
 * @param b
 * @return True if a < b, false otherwise
 */
inline bool lt(const double a, const double b) {
    return a + EPSILON < b;
}


/**
 * @brief Check if a greater than b
 * @param a
 * @param b
 * @return True if a > b, false otherwise
 */
inline bool gt(const double a, const double b) {
    return a - EPSILON > b;
}


/**
 * @brief Check if a is equal to b
 * @param a
 * @param b
 * @return True if a == b, false otherwise
 */
inline bool eq(const double a, const double b) {
    return std::abs(a - b) < EPSILON;
}


/**
 * @brief Check if a is not equal to b
 * @param a
 * @param b
 * @return True if a != b, false otherwise
 */
inline bool ne(const double a, const double b) {
    return std::abs(a - b) > EPSILON;
}

}

#endif //GEOMETRY_COMMON_HPP
