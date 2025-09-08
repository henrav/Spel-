//
// Created by Henrik Ravnborg on 2025-09-06.
//

#include "GameEngineAPI.h"
#include "ProjectileManager.h"
#include "EntityManager.h"
#include "../Entity.h"


void GameEngineAPI::spawnProjectile(std::shared_ptr<Projectile>& projectile){
    ProjectileManager::addProjectile(projectile);
}

void GameEngineAPI::draw(sf::RenderWindow& window) {
    ProjectileManager::drawProjectiles(window);
    EntityManager::drawEntities(window);
}

void GameEngineAPI::update(float dt) {
    ProjectileManager::update(dt);
}



 sf::Vector2f GameEngineAPI::getUnitPos(int id) {
    return EntityManager::find(id).getShape().getPosition();
}
