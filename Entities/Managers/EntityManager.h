//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_ENTITYMANAGER_H
#define UNTITLED13_ENTITYMANAGER_H



#include "iostream"
struct Entity;

class EntityManager {
private:
    static std::unordered_map<int, std::shared_ptr<Entity>> entityList;
    static int entityID;
public:


    template<class T, typename... Args>
    static Entity& addEntity(Args&&... args){
            static_assert(std::is_base_of_v<Entity, T>, "T must derive from Projectile");

            auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
            ptr->setId(entityID);

            auto& ref = *ptr;
            entityList.emplace(entityID++, std::move(ptr));
            return ref;
    }

    static Entity& find(int id);


    static void drawEntities(sf::RenderWindow& w);
};






#endif //UNTITLED13_ENTITYMANAGER_H
