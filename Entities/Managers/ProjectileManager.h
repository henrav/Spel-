//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_PROJECTILEMANAGER_H
#define UNTITLED13_PROJECTILEMANAGER_H



#include "iostream"
#include <SFML/Graphics/RenderWindow.hpp>

struct Projectile;
struct Vec2 {
    float x;
    float y;
};
class ProjectileManager {
private:
     std::unordered_map<int, std::shared_ptr<Projectile>> projectileList;
     int projectileID;
public:
    ProjectileManager() = default;
    ~ProjectileManager() = default;

    template<class T, typename... Args>
    Projectile& addProjectile(Args&&... args)
    {
        static_assert(std::is_base_of_v<Projectile, T>, "T must derive from Projectile");

        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        setID(projectileID, *ptr);

        auto& ref = *ptr;
        projectileList.emplace(projectileID++, std::move(ptr));
        return ref;
    }

    void setID(int id, Projectile& projectile);

     void update(const float dt);




     void drawProjectiles(sf::RenderWindow& w);


};


#endif //UNTITLED13_PROJECTILEMANAGER_H
