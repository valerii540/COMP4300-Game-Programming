#ifndef ASSIGNMENT_2_CONFIGLOADER_H
#define ASSIGNMENT_2_CONFIGLOADER_H

#include "../../libs/json.hpp"
#include <fstream>
#include "../Common.h"

using namespace nlohmann;

class ConfigLoader {
    struct WindowConfig {
        int  width, height, frameLimit;
        bool fullScreen;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(WindowConfig, width, height, frameLimit, fullScreen);
    };

    struct Color {
        int r, g, b;

        sf::Color toSFML() { return sf::Color(r, g, b); }

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Color, r, g, b);
    };

    struct FontConfig {
        std::string path;
        int         size;
        Color       color;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FontConfig, path, size, color);
    };

    struct PlayerConfig {
        int   shapeRadius, shapeVertices, collisionRadius, outlineThickness;
        Color fillColor, outlineColor;
        float speed;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayerConfig, shapeRadius, shapeVertices, collisionRadius, outlineThickness,
                                       fillColor, outlineColor, speed);
    };

    struct EnemyConfig {
        int   shapeRadius, collisionRadius, outlineThickness, minVertices, maxVertices, smallLifespan, spawnInterval;
        Color outlineColor;
        float minSpeed, maxSpeed;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(EnemyConfig, shapeRadius, collisionRadius, outlineThickness, minVertices,
                                       maxVertices, smallLifespan, spawnInterval, outlineColor, minSpeed, maxSpeed);
    };

    struct BulletConfig {
        int   shapeRadius, collisionRadius, outlineThickness, shapeVertices, lifespan;
        Color fillColor, outlineColor;
        float speed;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(BulletConfig, shapeRadius, collisionRadius, outlineThickness, shapeVertices,
                                       lifespan, fillColor, outlineColor, speed);
    };

public:
    struct GameConfig {
        WindowConfig window = WindowConfig();
        FontConfig   font   = FontConfig();
        PlayerConfig player = PlayerConfig();
        EnemyConfig  enemy  = EnemyConfig();
        BulletConfig bullet = BulletConfig();
    } config;

    ConfigLoader(const std::string &path);
};


#endif //ASSIGNMENT_2_CONFIGLOADER_H
