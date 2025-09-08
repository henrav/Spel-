//
// Created by Henrik Ravnborg on 2025-09-06.
//

#ifndef UNTITLED13_PROJECTILES_H
#define UNTITLED13_PROJECTILES_H

#endif //UNTITLED13_PROJECTILES_H
#include "../../Entities/Drawable.h"

struct Projectile : public Drawable {
    int id;
    int ownerID = 0;

    //optional
    int targetID = 0;

    float speed = 0;

    //optional
    sf::Vector2f targetLocation = {};

    std::function<void(Projectile& self)> onHit = [](Projectile& self){};
    std::function<void(Projectile& self)> update = [](Projectile& self){};
    std::function<void(Projectile& self)> onCollision = [](Projectile& self){};
};