#include "Game.h"

Game::Game(const std::string &configPath) {
    config_ = ConfigLoader::loadConfig(configPath);

    window_.create(sf::VideoMode(config_->window.width, config_->window.height),
                   "Assignment 2");
    window_.setFramerateLimit(config_->window.frameLimit);

    spawnPlayer();
}

void Game::run() {
    while (running_) {
        if (!paused_) {
            entityManager_.update();

            sCollision();
            sUserInput();
            sMovement();
            sEnemySpawner();
            sLifespan();

            currentFrame_++;
        }

        sRender();
    }

    window_.close();
}

void Game::sCollision() {
    for (const auto &enemy: entityManager_.getEntities("enemy")) {
        if (entitiesColliding(player_, enemy)) {
            player_->destroy();
            spawnPlayer();
        }

        for (const auto &bullet: entityManager_.getEntities("bullet")) {
            if (entitiesColliding(enemy, bullet)) {
                bullet->destroy();
                enemy->destroy();
            } else if (itCollidingWithWalls(bullet, bullet->cTransform->pos))
                bullet->destroy();
        }
    }
}


bool Game::itCollidingWithWalls(const std::shared_ptr<Entity> &entity, Vec2 &position) {
    float shapeRadius = entity->cShape->circle.getRadius();

    // @formatter:off
    return !(position.x > (0 + shapeRadius) &&
             position.x < (config_->window.width - shapeRadius) &&
             position.y > (0 + shapeRadius) &&
             position.y < (config_->window.height - shapeRadius));
    // @formatter:on
}

bool Game::entitiesColliding(const std::shared_ptr<Entity> &entity1, const std::shared_ptr<Entity> &entity2) {
    const Vec2   D    = entity1->cTransform->pos - entity2->cTransform->pos;
    const double DSq  = D.x * D.x + D.y * D.y;
    const double r1r2 = entity1->cShape->circle.getRadius() + entity2->cShape->circle.getRadius();

    return DSq < (r1r2) * (r1r2);
}

void Game::sMovement() {
    // Player movement
    if (player_->cInput->up) {
        float newYSpeed = player_->cTransform->speed.y - config_->player.speed;
        if (std::abs(newYSpeed) < config_->player.maxSpeed)
            player_->cTransform->speed.y = newYSpeed;
    }

    if (player_->cInput->down) {
        float newYSpeed = player_->cTransform->speed.y + config_->player.speed;
        if (std::abs(newYSpeed) < config_->player.maxSpeed)
            player_->cTransform->speed.y = newYSpeed;
    }

    if (player_->cInput->left) {
        float newXSpeed = player_->cTransform->speed.x - config_->player.speed;
        if (std::abs(newXSpeed) < config_->player.maxSpeed)
            player_->cTransform->speed.x = newXSpeed;
    }

    if (player_->cInput->right) {
        float newXSpeed = player_->cTransform->speed.x + config_->player.speed;
        if (std::abs(newXSpeed) < config_->player.maxSpeed)
            player_->cTransform->speed.x = newXSpeed;
    }


    if (!player_->cInput->up && !player_->cInput->down)
        player_->cTransform->speed.y *= 0.9f;

    if (!player_->cInput->left && !player_->cInput->right)
        player_->cTransform->speed.x *= 0.9f;

    Vec2 newPosition = player_->cTransform->pos + player_->cTransform->speed;
    if (!itCollidingWithWalls(player_, newPosition))
        player_->cTransform->pos = newPosition;
    else
        player_->cTransform->speed *= -1.f;

    //Bullets movement
    for (const auto &bullet: entityManager_.getEntities("bullet"))
        bullet->cTransform->pos += bullet->cTransform->speed;
}

void Game::sUserInput() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        running_ = false;
                        break;

                    case sf::Keyboard::A:
                        player_->cInput->left = true;
                        break;
                    case sf::Keyboard::D:
                        player_->cInput->right = true;
                        break;
                    case sf::Keyboard::W:
                        player_->cInput->up = true;
                        break;
                    case sf::Keyboard::S:
                        player_->cInput->down = true;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        running_ = false;
                        break;

                    case sf::Keyboard::A:
                        player_->cInput->left = false;
                        break;
                    case sf::Keyboard::D:
                        player_->cInput->right = false;
                        break;
                    case sf::Keyboard::W:
                        player_->cInput->up = false;
                        break;
                    case sf::Keyboard::S:
                        player_->cInput->down = false;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    spawnBullet(Vec2(event.mouseButton.x, event.mouseButton.y));
                break;
            case sf::Event::Closed:
                running_ = false;
                break;
            default:
                break;
        }
    }
}

void Game::sLifespan() {
    for (const auto &entity: entityManager_.getEntities())
        if (entity->cLifespan) {
            entity->cLifespan->remaining--;
            if (entity->cLifespan->remaining == 0) entity->destroy();
        }
}

void Game::sRender() {
    window_.clear();

    // Player rendering
    player_->cTransform->angle += 1.0f;
    player_->cShape->circle.setRotation(player_->cTransform->angle);
    player_->cShape->circle.setPosition(player_->cTransform->pos.x, player_->cTransform->pos.y);
    window_.draw(player_->cShape->circle);

    // Enemy rendering
    for (const auto &enemy: entityManager_.getEntities("enemy")) {
        enemy->cTransform->angle += 1.0f;
        enemy->cShape->circle.setRotation(enemy->cTransform->angle);
        enemy->cShape->circle.setPosition(enemy->cTransform->pos.x, enemy->cTransform->pos.y);
        window_.draw(enemy->cShape->circle);
    }

    //Bullet rendering
    for (const auto &bullet: entityManager_.getEntities("bullet")) {
        bullet->cShape->circle.setPosition(bullet->cTransform->pos.x, bullet->cTransform->pos.y);

        auto color = sf::Color(bullet->cShape->circle.getFillColor());
        color.a = 255 * bullet->cLifespan->remaining / config_->bullet.lifespan;
        bullet->cShape->circle.setFillColor(color);

        window_.draw(bullet->cShape->circle);
    }

    window_.display();
}

void Game::sEnemySpawner() {
    if (currentFrame_ - lastEnemySpawnTime_ >= config_->enemy.spawnInterval) {
        lastEnemySpawnTime_ = currentFrame_;

        auto distX        = std::uniform_int_distribution(
                (int) 0 + config_->enemy.shapeRadius,
                (int) window_.getSize().x - config_->enemy.shapeRadius
        );
        auto distY        = std::uniform_int_distribution(
                (int) 0 + config_->enemy.shapeRadius,
                (int) window_.getSize().y - config_->enemy.shapeRadius
        );
        auto distVertices = std::uniform_int_distribution(config_->enemy.minVertices, config_->enemy.maxVertices);
        auto distRGB      = std::uniform_int_distribution(0, 255);

        auto enemy = entityManager_.addEntity("enemy");
        enemy->cTransform = std::make_shared<CTransform>(
                Vec2(0),
                Vec2(0),
                Vec2(1),
                0
        );
        enemy->cShape     = std::make_shared<CShape>(
                config_->enemy.shapeRadius,
                distVertices(random_),
                sf::Color(distRGB(random_), distRGB(random_), distRGB(random_)),
                config_->enemy.outlineColor.toSFML(),
                config_->enemy.outlineThickness
        );

        while (true) {
            enemy->cTransform->pos = {(float) distX(random_), (float) distY(random_)};

            if (!entitiesColliding(player_, enemy))
                break;
        }
    }
}

void Game::spawnPlayer() {
    player_ = entityManager_.addEntity("player");

    Vec2 centerPos = Vec2(config_->window.width / 2.0, config_->window.height / 2.0);
    player_->cTransform = std::make_shared<CTransform>(centerPos, Vec2(0), Vec2(1),
                                                       0.0);

    player_->cShape = std::make_shared<CShape>(
            config_->player.shapeRadius,
            config_->player.shapeVertices,
            config_->player.fillColor.toSFML(),
            config_->player.outlineColor.toSFML(),
            config_->player.outlineThickness);

    player_->cInput = std::make_shared<CInput>();
}

void Game::spawnBullet(const Vec2 &mousePos) {
    auto bullet = entityManager_.addEntity("bullet");

    float angle = std::atan2(mousePos.y - player_->cTransform->pos.y, mousePos.x - player_->cTransform->pos.x);

    Vec2 direction = Vec2(std::cos(angle), std::sin(angle));
    direction.normalize();

    bullet->cTransform = std::make_shared<CTransform>(
            player_->cTransform->pos,
            direction * config_->bullet.speed,
            Vec2(1),
            0
    );

    auto invisibleOutline = config_->bullet.outlineColor.toSFML();
    invisibleOutline.a = 0;
    bullet->cShape     = std::make_shared<CShape>(
            config_->bullet.shapeRadius,
            config_->bullet.shapeVertices,
            config_->bullet.fillColor.toSFML(),
            invisibleOutline,
            config_->bullet.outlineThickness
    );

    bullet->cLifespan = std::make_shared<CLifespan>(config_->bullet.lifespan);
}
