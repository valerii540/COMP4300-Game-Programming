#include "Game.h"

Game::Game(const std::string &configPath) {
    m_config = ConfigLoader::loadConfig(configPath);

    m_window.create(sf::VideoMode(m_config->window.width, m_config->window.height),
                    "Assignment 2");
    m_window.setFramerateLimit(m_config->window.frameLimit);

    spawnPlayer();
}

void Game::run() {
    while (m_running) {
        if (!m_paused) {
            m_entityManager.update();

            sCollision();
            sUserInput();
            sMovement();
            sEnemySpawner();

            m_currentFrame++;
        }

        sRender();
    }

    m_window.close();
}

void Game::sCollision() {
    for (const auto &enemy: m_entityManager.getEntities("enemy")) {
        if (entitiesColliding(m_player, enemy)) {
            m_player->destroy();
            spawnPlayer();
        }

        for (const auto &bullet: m_entityManager.getEntities("bullet")) {
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
             position.x < (m_config->window.width - shapeRadius) &&
             position.y > (0 + shapeRadius) &&
             position.y < (m_config->window.height - shapeRadius));
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
    if (m_player->cInput->up) {
        float newYSpeed = m_player->cTransform->speed.y - m_config->player.speed;
        if (std::abs(newYSpeed) < m_config->player.maxSpeed)
            m_player->cTransform->speed.y = newYSpeed;
    }

    if (m_player->cInput->down) {
        float newYSpeed = m_player->cTransform->speed.y + m_config->player.speed;
        if (std::abs(newYSpeed) < m_config->player.maxSpeed)
            m_player->cTransform->speed.y = newYSpeed;
    }

    if (m_player->cInput->left) {
        float newXSpeed = m_player->cTransform->speed.x - m_config->player.speed;
        if (std::abs(newXSpeed) < m_config->player.maxSpeed)
            m_player->cTransform->speed.x = newXSpeed;
    }

    if (m_player->cInput->right) {
        float newXSpeed = m_player->cTransform->speed.x + m_config->player.speed;
        if (std::abs(newXSpeed) < m_config->player.maxSpeed)
            m_player->cTransform->speed.x = newXSpeed;
    }


    if (!m_player->cInput->up && !m_player->cInput->down)
        m_player->cTransform->speed.y *= 0.9f;

    if (!m_player->cInput->left && !m_player->cInput->right)
        m_player->cTransform->speed.x *= 0.9f;

    Vec2 newPosition = m_player->cTransform->pos + m_player->cTransform->speed;
    if (!itCollidingWithWalls(m_player, newPosition))
        m_player->cTransform->pos = newPosition;
    else
        m_player->cTransform->speed *= -1.f;

    //Bullets movement
    for (const auto &bullet: m_entityManager.getEntities("bullet"))
        bullet->cTransform->pos += bullet->cTransform->speed;
}

void Game::sUserInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        m_running = false;
                        break;

                    case sf::Keyboard::A:
                        m_player->cInput->left = true;
                        break;
                    case sf::Keyboard::D:
                        m_player->cInput->right = true;
                        break;
                    case sf::Keyboard::W:
                        m_player->cInput->up = true;
                        break;
                    case sf::Keyboard::S:
                        m_player->cInput->down = true;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        m_running = false;
                        break;

                    case sf::Keyboard::A:
                        m_player->cInput->left = false;
                        break;
                    case sf::Keyboard::D:
                        m_player->cInput->right = false;
                        break;
                    case sf::Keyboard::W:
                        m_player->cInput->up = false;
                        break;
                    case sf::Keyboard::S:
                        m_player->cInput->down = false;
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
                m_running = false;
                break;
            default:
                break;
        }
    }
}

void Game::sLifespan() {

}

void Game::sRender() {
    m_window.clear();

    for (const auto &entity: m_entityManager.getEntities())
        if (entity->cShape && entity->cTransform) {
            entity->cTransform->angle += 1.0f;
            entity->cShape->circle.setRotation(entity->cTransform->angle);
            entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);
            m_window.draw(entity->cShape->circle);
        }

    m_window.display();
}

void Game::sEnemySpawner() {
    if (m_currentFrame - m_lastEnemySpawnTime >= m_config->enemy.spawnInterval) {
        m_lastEnemySpawnTime = m_currentFrame;

        auto distX        = std::uniform_int_distribution(
                (int) 0 + m_config->enemy.shapeRadius,
                (int) m_window.getSize().x - m_config->enemy.shapeRadius
        );
        auto distY        = std::uniform_int_distribution(
                (int) 0 + m_config->enemy.shapeRadius,
                (int) m_window.getSize().y - m_config->enemy.shapeRadius
        );
        auto distVertices = std::uniform_int_distribution(m_config->enemy.minVertices, m_config->enemy.maxVertices);
        auto distRGB      = std::uniform_int_distribution(0, 255);

        auto enemy = m_entityManager.addEntity("enemy");
        enemy->cTransform = std::make_shared<CTransform>(
                Vec2(0),
                Vec2(0),
                Vec2(1),
                0
        );
        enemy->cShape     = std::make_shared<CShape>(
                m_config->enemy.shapeRadius,
                distVertices(m_random),
                sf::Color(distRGB(m_random), distRGB(m_random), distRGB(m_random)),
                m_config->enemy.outlineColor.toSFML(),
                m_config->enemy.outlineThickness
        );

        while (true) {
            enemy->cTransform->pos = {(float) distX(m_random), (float) distY(m_random)};

            if (!entitiesColliding(m_player, enemy))
                break;
        }
    }
}

void Game::spawnPlayer() {
    m_player = m_entityManager.addEntity("player");

    Vec2 centerPos = Vec2(m_config->window.width / 2.0, m_config->window.height / 2.0);
    m_player->cTransform = std::make_shared<CTransform>(centerPos, Vec2(0), Vec2(1),
                                                        0.0);

    m_player->cShape = std::make_shared<CShape>(
            m_config->player.shapeRadius,
            m_config->player.shapeVertices,
            m_config->player.fillColor.toSFML(),
            m_config->player.outlineColor.toSFML(),
            m_config->player.outlineThickness);

    m_player->cInput = std::make_shared<CInput>();
}

void Game::spawnBullet(const Vec2 &mousePos) {
    auto bullet = m_entityManager.addEntity("bullet");

    float angle = std::atan2(mousePos.y - m_player->cTransform->pos.y, mousePos.x - m_player->cTransform->pos.x);

    Vec2 direction = Vec2(std::cos(angle), std::sin(angle));
    direction.normalize();

    bullet->cTransform = std::make_shared<CTransform>(
            m_player->cTransform->pos,
            direction * m_config->bullet.speed,
            Vec2(1),
            0
    );

    bullet->cShape = std::make_shared<CShape>(
            m_config->bullet.shapeRadius,
            m_config->bullet.shapeVertices,
            m_config->bullet.fillColor.toSFML(),
            m_config->bullet.outlineColor.toSFML(),
            m_config->bullet.outlineThickness
    );
}
