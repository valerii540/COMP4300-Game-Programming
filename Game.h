#ifndef ASSIGNMENT_2_GAME_H
#define ASSIGNMENT_2_GAME_H

#include "game-engine/Common.h"
#include "game-engine/EntityManager.h"
#include "game-engine/util/ConfigLoader.h"

class Game {
    ConfigLoader     m_configLoader;
    sf::RenderWindow m_window;
    EntityManager    m_entityManager;
    sf::Font         m_font;
    sf::Text         m_text;
    int              m_score              = 0;
    int              m_currentFrame       = 0;
    int              m_lastEnemySpawnTime = 0;
    bool             m_paused             = false;
    bool             m_running            = true;

    std::shared_ptr<Entity> m_player;

    void init();

    void setPaused(bool paused);

    void sMovement();

    void sUserInput();

    void sLifespan();

    void sRender();

    void sEnemySpawner();

    void sCollision();

    void spawnPlayer();

    void spawnEnemy();

    void spawnSmallEnemies(std::shared_ptr<Entity> entity);

    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos);

    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    Game(const std::string &configPath);

    void run();
};


#endif //ASSIGNMENT_2_GAME_H