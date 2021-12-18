#ifndef COMP4300_GAME_PROGRAMMING_CTRANSFORM_H
#define COMP4300_GAME_PROGRAMMING_CTRANSFORM_H

#include "../util/Vec2.h"

class CTransform {
public:
    Vec2   pos   = {0.0, 0.0};
    Vec2   speed = {0.0, 0.0};
    Vec2   scale = {1.0, 1.0};
    double angle = 0.0;

    CTransform(Vec2 &pos, Vec2 &speed, Vec2 &scale, double angle) :
            pos(pos), speed(speed), scale(scale), angle(angle) {};
};

#endif //COMP4300_GAME_PROGRAMMING_CTRANSFORM_H
