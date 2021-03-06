#ifndef COMP4300_GAME_PROGRAMMING_ENTITYMANAGER_H
#define COMP4300_GAME_PROGRAMMING_ENTITYMANAGER_H

#include "Common.h"
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec>     EntityMap;

class EntityManager {
    EntityVec entities_;
    EntityVec entitiesToAdd_;
    EntityMap entityMap_;
    size_t    totalEntities_ = 0;

    void removeDeadEntities(EntityVec &vec);

public:
    void update();

    std::shared_ptr<Entity> addEntity(const std::string &tag);

    const EntityVec &getEntities();

    const EntityVec &getEntities(const std::string &tag);
};


#endif //COMP4300_GAME_PROGRAMMING_ENTITYMANAGER_H
