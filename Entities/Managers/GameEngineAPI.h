//
// Created by Henrik Ravnborg on 2025-09-06.
//

#ifndef UNTITLED13_GAMEENGINEAPI_H
#define UNTITLED13_GAMEENGINEAPI_H

#pragma once
#include <functional>
#include <memory>
#include <utility>
#include "SFML/Graphics.hpp"

// Forward decls that match your project
struct Entity;
struct Projectile;
class GameMap;

#include "EntityManager.h"
#include "ProjectileManager.h"
#include "../../Map/GameMap.h"

namespace Engine {
    namespace detail {
        struct State {
            GameMap*            map               = nullptr;
            EntityManager*      entityManager     = nullptr;
            ProjectileManager*  projectileManager = nullptr;
            bool                initialized       = false;

            [[nodiscard]] GameMap&            Map() const             { assert(map);               return *map; }
            [[nodiscard]] EntityManager&      EM() const              { assert(entityManager);     return *entityManager; }
            [[nodiscard]] ProjectileManager&  PM() const              { assert(projectileManager); return *projectileManager; }
      
        };

        inline State &state() {
            static State s;
            return s;
        }
    }


    inline void init(GameMap& map, EntityManager& em, ProjectileManager& pm) noexcept {
        auto& s = detail::state();
        s.map               = &map;
        s.entityManager     = &em;
        s.projectileManager = &pm;
        s.initialized       = true;
        s.map->attachListeners();
    }
    template<class T, class... Args>
    inline Entity& addEntity(Args&&... args) {
        return detail::state().EM().template addEntity<T>(std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    inline Projectile& spawnProjectile(Args&&... args) {
        return detail::state().PM().template addProjectile<T>(std::forward<Args>(args)...);
    }

    inline void update(float dt) noexcept {
        detail::state().PM().update(dt);
    }

    inline void draw(sf::RenderWindow& window) {
        detail::state().Map().drawMap(window);
        detail::state().PM().drawProjectiles(window);
        detail::state().EM().drawEntities(window);
    }


    inline sf::Vector2f getUnitPos(int id){
        return detail::state().EM().getUnitPos(id);
    }

    inline void setUnitPos(sf::Vector2f pos, int id ){
        detail::state().EM().setUnitPos(pos, id);
    }

    inline sf::Vector2f getMapCenter(){
        return detail::state().Map().getCenter();
    }

    inline Entity& getEntity(int id){
        return detail::state().EM().find(id);
    }

}



#endif //UNTITLED13_GAMEENGINEAPI_H
