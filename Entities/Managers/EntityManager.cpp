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

