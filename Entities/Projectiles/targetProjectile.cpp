//
// Created by Henrik Ravnborg on 2025-07-28.
//

#include "targetProjectile.h"
#include "../Managers/EntityManager.h"

void targetProjectile::update(float dt) {
    Entity entity = EntityManager::find(this->targetID);
    sf::Vector2f pos =entity.getShape().getPosition();
    const sf::Vector2f currentPos = getShape().getPosition();

    /* 2. Compute unit direction */
    sf::Vector2f dir = pos - currentPos;
    const float len2 = dir.x * dir.x + dir.y * dir.y;
    if (len2 == 0.f) return;

    const float len = std::sqrt(len2);
    dir /= len;


    const sf::Vector2f step = dir * speed * dt ;
    shape.move(step);

    if (this->shape.getGlobalBounds().findIntersection(entity.getShape().getGlobalBounds())){
        this->dead = false;
    }



}


