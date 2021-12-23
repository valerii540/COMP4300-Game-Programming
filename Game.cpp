#include "Game.h"
#include <iostream>

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
    switch (m_player->cInput->action) {
        case CInputNS::None:
            if (std::abs(m_player->cTransform->speed.x) <= 0.2f)
                m_player->cTransform->speed.x = 0;
            else
                m_player->cTransform->speed.x -= m_player->cTransform->speed.x > 0 ? 0.2f : -0.2f;

            if (std::abs(m_player->cTransform->speed.y) <= 0.2f)
                m_player->cTransform->speed.y = 0;
            else
                m_player->cTransform->speed.y -= m_player->cTransform->speed.y > 0 ? 0.2f : -0.2f;
            break;
        case CInputNS::Up: {
            float newYSpeed = m_player->cTransform->speed.y - m_config->player.speed;
            if (std::abs(newYSpeed) < m_config->player.maxSpeed)
                m_player->cTransform->speed.y -= m_config->player.speed;
            break;
        }
        case CInputNS::Left: {
            float newXSpeed = m_player->cTransform->speed.x - m_config->player.speed;
            if (std::abs(newXSpeed) < m_config->player.maxSpeed)
                m_player->cTransform->speed.x -= m_config->player.speed;
            break;
        }
        case CInputNS::Right: {
            float newXSpeed = m_player->cTransform->speed.x + m_config->player.speed;
            if (std::abs(newXSpeed) < m_config->player.maxSpeed)
                m_player->cTransform->speed.x += m_config->player.speed;
            break;
        }
        case CInputNS::Down: {
            float newYSpeed = m_player->cTransform->speed.y + m_config->player.speed;
            if (std::abs(newYSpeed) < m_config->player.maxSpeed)
                m_player->cTransform->speed.y += m_config->player.speed;
            break;
        }
        case CInputNS::Shoot:
            break;
    }

    Vec2 newPosition = m_player->cTransform->pos + m_player->cTransform->speed;
    if (newPosition.x > (0 + m_config->player.shapeRadius) &&
        newPosition.x<(m_config->window.width - m_config->player.shapeRadius) &&
                      newPosition.y>(0 + m_config->player.shapeRadius) &&
        newPosition.y < (m_config->window.height - m_config->player.shapeRadius)) {

        m_player->cTransform->pos = newPosition;
    }

    m_player->cInput->action = CInputNS::None;
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
                        m_player->cInput->action = CInputNS::Left;
                        break;
                    case sf::Keyboard::D:
                        m_player->cInput->action = CInputNS::Right;
                        break;
                    case sf::Keyboard::W:
                        m_player->cInput->action = CInputNS::Up;
                        break;
                    case sf::Keyboard::S:
                        m_player->cInput->action = CInputNS::Down;
                        break;
                    default:
                        break;
                }
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

    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);

    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);

    m_window.draw(m_player->cShape->circle);

    m_window.display();
}

void Game::sEnemySpawner() {

}

void Game::spawnPlayer() {

}
