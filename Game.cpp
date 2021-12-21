#include "Game.h"

Game::Game(const std::string &configPath) {
    init(configPath);
}

void Game::init(const std::string &configPath) {
    //TODO: read config


    m_player = m_entityManager.addEntity("player");
    m_player->cTransform = std::make_shared<CTransform>(Vec2(100, 100), Vec2(0, 0), Vec2(1, 1), 90.0);
    m_player->cShape = std::make_shared<CShape>(50.f, 5, sf::Color::Cyan, sf::Color::Green, 2);
//    m_player->cTransform->pos = Vec2(100, 100);


    m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
    m_window.setFramerateLimit(60);

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
