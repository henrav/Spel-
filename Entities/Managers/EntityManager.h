//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_ENTITYMANAGER_H
#define UNTITLED13_ENTITYMANAGER_H


#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Drawable.h"
#include "../Entity.h"

class EntityManager {
private:
    static std::unordered_map<int, std::unique_ptr<Entity>> entityList;
    static int entityID;
public:


    template<class T, typename... Args>
    static Entity& addEntity(Args&&... args)
    {
        static_assert(std::is_base_of_v<Entity, T>, "T must derive from Projectile");

        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        ptr->setId(entityID);

        auto& ref = *ptr;
        entityList.emplace(entityID++, std::move(ptr));
        return ref;
    }

    static Entity& find(int id){
        return *entityList.find(id)->second;
    }

    static void drawEntities(sf::RenderWindow& w)
    {
        for (const auto& e : entityList){
            w.draw(e.second->getShape());
        }

    }
};






#endif //UNTITLED13_ENTITYMANAGER_H
