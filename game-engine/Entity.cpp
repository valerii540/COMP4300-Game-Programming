#include "Entity.h"


Entity::Entity(size_t id, const std::string &tag) : id_(id), tag_(tag) {}

bool Entity::isActive() const {
    return active_;
}

const std::string &Entity::tag() const {
    return tag_;
}

const size_t &Entity::id() const {
    return id_;
}

void Entity::destroy() {
    active_ = false;
}

