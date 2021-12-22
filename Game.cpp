#include "Game.h"

Game::Game(const std::string &configPath) :
        m_configLoader(configPath) {
    init();
}

void Game::init() {
    m_player = m_entityManager.addEntity("player");

    Vec2 centerPos = Vec2(m_configLoader.config.window.width / 2.0, m_configLoader.config.window.height / 2.0);
    m_player->cTransform = std::make_shared<CTransform>(centerPos, Vec2(0, 0), Vec2(1, 1), 0.0);

    m_player->cShape = std::make_shared<CShape>(
            m_configLoader.config.player.shapeRadius,
            m_configLoader.config.player.shapeVertices,
            m_configLoader.config.player.fillColor.toSFML(),
            m_configLoader.config.player.outlineColor.toSFML(),
            m_configLoader.config.player.outlineThickness);


    m_window.create(sf::VideoMode(m_configLoader.config.window.width, m_configLoader.config.window.height),
                    "Assignment 2");
    m_window.setFramerateLimit(m_configLoader.config.window.frameLimit);

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
}

void Game::sCollision() {

}

void Game::sMovement() {

}

void Game::sUserInput() {

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
