#ifndef COMP4300_GAME_PROGRAMMING_CSHAPE_H
#define COMP4300_GAME_PROGRAMMING_CSHAPE_H

#include <SFML/Graphics/CircleShape.hpp>

class CShape {
public:
    sf::CircleShape circle;

    CShape(float radius, int points, const sf::Color &fill, const sf::Color &outline, float thickness)
            : circle(radius, points) {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

#endif //COMP4300_GAME_PROGRAMMING_CSHAPE_H
