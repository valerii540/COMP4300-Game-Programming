#ifndef COMP4300_GAME_PROGRAMMING_ENTITY_H
#define COMP4300_GAME_PROGRAMMING_ENTITY_H

#include "Common.h"
#include "components/CTransform.h"
#include "components/CShape.h"
#include "components/CCollision.h"
#include "components/CInput.h"
#include "components/CLifespan.h"
#include "components/CScore.h"


class Entity {
    friend class EntityManager;

    std::string m_tag    = "default";
    bool        m_active = true;
    size_t      m_id     = 0;

    Entity(size_t id, const std::string &tag);

public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape>     cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput>     cInput;
    std::shared_ptr<CScore>     cScore;
    std::shared_ptr<CLifespan>  cLifespan;

    [[nodiscard]] bool isActive() const;

    [[nodiscard]] const std::string &tag() const;

    [[nodiscard]] const size_t &id() const;

    void destroy();
};

#endif //COMP4300_GAME_PROGRAMMING_ENTITY_H
