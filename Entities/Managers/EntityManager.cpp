//
// Created by Henrik Ravnborg on 2025-07-27.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"
#include "../Entity.h"

void EntityManager::drawEntities(sf::RenderWindow &w) {
    for (const auto& e : entityList){
        w.draw(e.second->getShape());
    }
}

Entity& EntityManager::find(int id) {
    auto it = entityList.find(id);
    if (it == entityList.end()) throw std::runtime_error("Entity not found");
    return *(it->second);
}


Entity* EntityManager::tryFind(int id) noexcept {
    auto it = entityList.find(id);
    return (it == entityList.end()) ? nullptr : it->second.get();
}

sf::Vector2f EntityManager::getUnitPos(int id) {
   // std::cout << "finding player with id: " << id << std::endl;
    auto* e = tryFind(id);
    assert(e && "EntityManager::getUnitPos: invalid id");
    return e ? e->getShape().getPosition() : sf::Vector2f();
}

void EntityManager::setID(int id, Entity &entity){
    entity.setId(id);
}

void EntityManager::setUnitPos(sf::Vector2f pos, int id) {
    auto* e = tryFind(id);
    assert(e && "EntityManager::setUnitPos: invalid id");
    e->setShapePos(pos) ;
}



