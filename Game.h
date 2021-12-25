#ifndef ASSIGNMENT_2_GAME_H
#define ASSIGNMENT_2_GAME_H

#include "game-engine/Common.h"
#include "game-engine/EntityManager.h"
#include "game-engine/util/ConfigLoader.h"
#include <cmath>

class Game {
    std::shared_ptr<ConfigLoader::GameConfig> m_config;
    sf::RenderWindow                          m_window;
    EntityManager                             m_entityManager;
    sf::Font                                  m_font;
    sf::Text                                  m_text;
    int                                       m_score              = 0;
    int                                       m_currentFrame       = 0;
    int                                       m_lastEnemySpawnTime = 0;
    bool                                      m_paused             = false;
    bool                                      m_running            = true;

    std::shared_ptr<Entity> m_player;

    void init(const std::string &configPath);

    void setPaused(bool paused);

    void sMovement();

    void sUserInput();

    void sLifespan();

    void sRender();

    void sEnemySpawner();

    void sCollision();

    bool itCollidingWithWalls(const std::shared_ptr<Entity> &entity, Vec2 &position);

    void spawnPlayer();

    void spawnEnemy();

    void spawnSmallEnemies(std::shared_ptr<Entity> entity);

    void spawnBullet(const Vec2 &mousePos);

    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    Game(const std::string &configPath);

    void run();
};


#endif //ASSIGNMENT_2_GAME_H
