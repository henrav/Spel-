//
// Created by Henrik Ravnborg on 2025-07-27.
//

#include "ProjectileManager.h"
#include "../Projectiles/Projectiles.h"




void ProjectileManager::update(const float dt) {
    for (const auto& e : projectileList){
        e.second->update(*e.second);
    }
}

void ProjectileManager::drawProjectiles(sf::RenderWindow &w) {
    for (const auto& e : projectileList){
        w.draw(e.second->getShape());
    }
}

void ProjectileManager::setID(int id, Projectile& projectile) {
    projectile.id = id;
}
