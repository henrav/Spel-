//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_ENTITYMANAGER_H
#define UNTITLED13_ENTITYMANAGER_H



#include "iostream"
struct Entity;

class EntityManager {
private:
    std::unordered_map<int, std::shared_ptr<Entity>> entityList;
    int nextId = 1;
public:
    EntityManager() = default;
    ~EntityManager() = default;

    template<class T, class... Args>
    T& addEntity(Args&&... args) {
        static_assert(std::is_base_of_v<Entity, T>, "T must derive from Entity");

        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        std::cout<< "playerid: " << nextId << std::endl;
        setID(nextId, *ptr);

        auto& ref = *ptr;
        entityList.emplace(nextId++, std::move(ptr));
        return static_cast<T&>(ref);
    }

        void setID(int id, Entity &entity);

     Entity& find(int id);
     Entity* tryFind(int id) noexcept;

     sf::Vector2f getUnitPos(int id);

    void drawEntities(sf::RenderWindow& w);

    void clear() { entityList.clear(); nextId = 1; }

    void setUnitPos(sf::Vector2f, int id);
};






#endif //UNTITLED13_ENTITYMANAGER_H
