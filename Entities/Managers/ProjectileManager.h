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
    static std::unordered_map<int, std::shared_ptr<Projectile>> projectileList;
    static int projectileID;
public:


    static void addProjectile(std::shared_ptr<Projectile> projectile);



    /*
     *
     * template<class T, typename... Args>
    static Projectile& addProjectile(Args&&... args)
    {
        static_assert(std::is_base_of_v<Projectile, T>, "T must derive from Projectile");

        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        ptr->setId(projectileID);

        auto& ref = *ptr;
        projectileList.emplace(projectileID++, std::move(ptr));
        return ref;
    }
     */


    static void update(const float dt);




    static void drawProjectiles(sf::RenderWindow& w);


};


#endif //UNTITLED13_PROJECTILEMANAGER_H
