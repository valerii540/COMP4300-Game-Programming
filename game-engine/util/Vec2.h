#ifndef COMP4300_GAME_PROGRAMMING_VEC2_H
#define COMP4300_GAME_PROGRAMMING_VEC2_H

#include <cmath>

class Vec2 {
public:
    double x = 0.0;
    double y = 0.0;

    Vec2(double x, double y) : x(x), y(y) {}

    [[nodiscard]] double length() const;

    [[maybe_unused]] void normalize();

    friend bool operator==(Vec2 const &v1, Vec2 const &v2);

    friend bool operator!=(Vec2 const &v1, Vec2 const &v2);

    friend Vec2 operator+(Vec2 const &v1, Vec2 const &v2);

    friend Vec2 operator-(Vec2 const &v1, Vec2 const &v2);

    friend Vec2 operator*(Vec2 const &v1, Vec2 const &v2);

    friend Vec2 operator/(Vec2 const &v1, Vec2 const &v2);
};


#endif //COMP4300_GAME_PROGRAMMING_VEC2_H
