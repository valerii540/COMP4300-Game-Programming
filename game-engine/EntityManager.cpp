#include "EntityManager.h"

void EntityManager::removeDeadEntities(EntityVec &vec) {
    erase_if(vec,
             [&](const std::shared_ptr<Entity> &item) {
                 return !item->isActive();
             });
}

void EntityManager::update() {
    m_entities.insert(
            m_entities.end(),
            m_entitiesToAdd.begin(),
            m_entitiesToAdd.end()
    );

    for (const auto& entityToAdd: m_entitiesToAdd)
        m_entityMap[entityToAdd->tag()].push_back(entityToAdd);

    m_entitiesToAdd.clear();

    removeDeadEntities(m_entities);

    for (auto &[tag, entities]: m_entityMap)
        removeDeadEntities(entities);
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

    m_entitiesToAdd.push_back(entity);

    return entity;
}

const EntityVec &EntityManager::getEntities() {
    return m_entities;
}

const EntityVec &EntityManager::getEntities(const std::string &tag) {
    return m_entityMap[tag];
}
