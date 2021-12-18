#include "Vec2.h"

double Vec2::length() const {
    return sqrt(x * x + y * y);
}

void Vec2::normalize() {
    double length = Vec2::length();
    x /= length;
    y /= length;
}

bool operator==(Vec2 const &v1, Vec2 const &v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const Vec2 &v1, const Vec2 &v2) {
    return v1.x != v2.x || v1.y != v2.y;
}

Vec2 operator+(const Vec2 &v1, const Vec2 &v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

Vec2 operator-(const Vec2 &v1, const Vec2 &v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

Vec2 operator*(const Vec2 &v1, const Vec2 &v2) {
    return {v1.x * v2.x, v1.y * v2.y};
}

Vec2 operator/(const Vec2 &v1, const Vec2 &v2) {
    return {v1.x / v2.x, v1.y / v2.y};
}


