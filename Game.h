#ifndef ASSIGNMENT_2_GAME_H
#define ASSIGNMENT_2_GAME_H

#include "game-engine/Common.h"
#include "game-engine/EntityManager.h"
#include "game-engine/util/ConfigLoader.h"
#include <cmath>
#include <random>

class Game {
    std::shared_ptr<ConfigLoader::GameConfig> config_;
    sf::RenderWindow                          window_;
    EntityManager                             entityManager_;
    sf::Font                                  font_;
    sf::Text                                  text_;
    int                                       score_              = 0;
    int                                       currentFrame_       = 0;
    int                                       lastEnemySpawnTime_ = 0;
    bool                                      paused_             = false;
    bool                                      running_            = true;
    std::mt19937                              random_             = std::mt19937(time(nullptr));

    std::shared_ptr<Entity> player_;

    void setPaused(bool paused);

    void sMovement();

    void sUserInput();

    void sLifespan();

    void sRender();

    void sEnemySpawner();

    void sCollision();

    bool itCollidingWithWalls(const std::shared_ptr<Entity> &entity, Vec2 &position);

    static bool entitiesColliding(const std::shared_ptr<Entity> &entity1, const std::shared_ptr<Entity> &entity2);

    void spawnPlayer();

    void spawnEnemy();

    void spawnSmallEnemies(std::shared_ptr<Entity> entity);

    void spawnBullet(const Vec2 &mousePos);

    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    explicit Game(const std::string &configPath);

    void run();
};


#endif //ASSIGNMENT_2_GAME_H
