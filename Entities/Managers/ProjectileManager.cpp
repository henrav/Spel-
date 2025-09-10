//
// Created by Henrik Ravnborg on 2025-07-27.
//

#include "ProjectileManager.h"
#include "../Projectiles/Projectiles.h"

void ProjectileManager::addProjectile(std::shared_ptr<Projectile> projectile) {
    projectile->id = projectileID;
    projectileList.emplace(projectileID++, std::move(projectile));
}





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