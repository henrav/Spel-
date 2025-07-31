//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_PROJECTILEMANAGER_H
#define UNTITLED13_PROJECTILEMANAGER_H


#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Projectiles/targetProjectile.h"

class ProjectileManager {
    static std::unordered_map<int, std::unique_ptr<Projectile>> projectileList;
    static int projectileID;
public:


    template<class T, typename... Args>
    static Projectile& addProjectile(Args&&... args)
    {
        static_assert(std::is_base_of_v<Projectile, T>, "T must derive from Projectile");

        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        ptr->setId(projectileID);

        auto& ref = *ptr;
        projectileList.emplace(projectileID++, std::move(ptr));
        return ref;
    }

    static void update(const float dt) {
        for (const auto& e : projectileList){
            e.second->update(dt);
        }
    }




    static void drawProjectiles(sf::RenderWindow& w){
        for (const auto& e : projectileList){
            w.draw(e.second->getShape());
        }

    }


};


#endif //UNTITLED13_PROJECTILEMANAGER_H
