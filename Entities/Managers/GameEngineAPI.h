//
// Created by Henrik Ravnborg on 2025-09-06.
//

#ifndef UNTITLED13_GAMEENGINEAPI_H
#define UNTITLED13_GAMEENGINEAPI_H

#pragma once
#include <functional>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"

struct Projectile;
struct Entity;

struct GameEngineAPI {
    static void spawnProjectile (std::shared_ptr<Projectile>& projectile);
    static void draw(sf::RenderWindow& window);
    std::function<void(int targetId, int dmg)>       dealDamage;
    std::function<float()>                           timeSeconds;
    static void update(float dt);

    template<class T, typename... Args>
    static Entity& addEntity(Args&&... args){
        return EntityManager::addEntity<T>(std::forward<Args>(args)...);
    }


    static  sf::Vector2f getUnitPos(int id);
};


#endif //UNTITLED13_GAMEENGINEAPI_H
