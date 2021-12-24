#include "Game.h"

Game::Game(const std::string &configPath) {
    init(configPath);
}

void Game::init(const std::string &configPath) {
    m_config = ConfigLoader::loadConfig(configPath);

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
        m_player->cTransform->speed.y *= 0.9;

    if (!m_player->cInput->left && !m_player->cInput->right)
        m_player->cTransform->speed.x *= 0.9;

    Vec2 newPosition = m_player->cTransform->pos + m_player->cTransform->speed;
    if (newPosition.x > (0 + m_config->player.shapeRadius) &&
        newPosition.x<(m_config->window.width - m_config->player.shapeRadius) &&
                      newPosition.y>(0 + m_config->player.shapeRadius) &&
        newPosition.y < (m_config->window.height - m_config->player.shapeRadius)) {

        m_player->cTransform->pos = newPosition;
    } else {
        m_player->cTransform->speed.x *= -1.f;
        m_player->cTransform->speed.y *= -1.f;
    }

    //Bullets movement
    for (const auto &bullet: m_entityManager.getEntities("bullet"))
        bullet->cTransform->pos = bullet->cTransform->pos + bullet->cTransform->speed;
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

    // Player rendering
    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);

    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);

    m_window.draw(m_player->cShape->circle);

    // Bullets rendering
    for (auto bullet: m_entityManager.getEntities("bullet")) {
        bullet->cShape->circle.setPosition(bullet->cTransform->pos.x, bullet->cTransform->pos.y);
        m_window.draw(bullet->cShape->circle);
    }

    m_window.display();
}

void Game::sEnemySpawner() {

}

void Game::spawnPlayer() {

}

void Game::spawnBullet(const Vec2 &mousePos) {
    auto bullet = m_entityManager.addEntity("bullet");

    float angle = std::atan2(mousePos.y - m_player->cTransform->pos.y, mousePos.x - m_player->cTransform->pos.x);

    Vec2 direction = Vec2(std::cos(angle), std::sin(angle));
    direction.normalize();

    bullet->cTransform = std::make_shared<CTransform>(
            m_player->cTransform->pos,
            direction * Vec2(m_config->bullet.speed),
            Vec2(1),
            0.0
    );

    bullet->cShape = std::make_shared<CShape>(
            m_config->bullet.shapeRadius,
            m_config->bullet.shapeVertices,
            m_config->bullet.fillColor.toSFML(),
            m_config->bullet.outlineColor.toSFML(),
            m_config->bullet.outlineThickness
    );
}
