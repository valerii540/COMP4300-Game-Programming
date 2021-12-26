#include "EntityManager.h"

void EntityManager::removeDeadEntities(EntityVec &vec) {
    erase_if(vec,
             [&](const std::shared_ptr<Entity> &item) {
                 return !item->isActive();
             });
}

void EntityManager::update() {
    entities_.insert(
            entities_.end(),
            entitiesToAdd_.begin(),
            entitiesToAdd_.end()
    );

    for (const auto &entityToAdd: entitiesToAdd_)
        entityMap_[entityToAdd->tag()].push_back(entityToAdd);

    entitiesToAdd_.clear();

    removeDeadEntities(entities_);

    for (auto &[tag, entities]: entityMap_)
        removeDeadEntities(entities);
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
    auto entity = std::shared_ptr<Entity>(new Entity(totalEntities_++, tag));

    entitiesToAdd_.push_back(entity);

    return entity;
}

const EntityVec &EntityManager::getEntities() {
    return entities_;
}

const EntityVec &EntityManager::getEntities(const std::string &tag) {
    return entityMap_[tag];
}
