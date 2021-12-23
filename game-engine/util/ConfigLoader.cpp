#include "ConfigLoader.h"

std::shared_ptr<ConfigLoader::GameConfig> ConfigLoader::loadConfig(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Cannot open config file");

    json jsonConfig;
    file >> jsonConfig;
    file.close();

    auto config = std::make_shared<GameConfig>();
    config->window = jsonConfig.at("window").get<WindowConfig>();
    config->font   = jsonConfig.at("font").get<FontConfig>();
    config->player = jsonConfig.at("player").get<PlayerConfig>();
    config->enemy  = jsonConfig.at("enemy").get<EnemyConfig>();
    config->bullet = jsonConfig.at("bullet").get<BulletConfig>();

    return config;
}
