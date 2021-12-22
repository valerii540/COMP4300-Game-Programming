#include "ConfigLoader.h"

ConfigLoader::ConfigLoader(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Cannot open config file");

    json jsonConfig;
    file >> jsonConfig;
    file.close();

    gameConfig.window = jsonConfig.at("window").get<WindowConfig>();
    gameConfig.font   = jsonConfig.at("font").get<FontConfig>();
    gameConfig.player = jsonConfig.at("player").get<PlayerConfig>();
    gameConfig.enemy  = jsonConfig.at("enemy").get<EnemyConfig>();
    gameConfig.bullet = jsonConfig.at("bullet").get<BulletConfig>();
}
