//
// Created by Henrik Ravnborg on 2025-10-14.
//

#ifndef UNTITLED13_GAMEMAP_H
#define UNTITLED13_GAMEMAP_H
#include "iostream"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

enum Type{
    WALL,
    GROUND
};

struct detailedData{
    Type type;
    float x;
    float y;

    detailedData(Type type, float x, float y) : type(type), x(x), y(y){};

};

class GameMap {
private:
    vector<sf::RectangleShape> map;
    vector<vector<bool>> mapData;
    int tileSize = 10;
    sf::Vector2f center;
    vector<detailedData> ground;
    vector<detailedData> walls;

public:
    GameMap();

    void loadMap();

    void drawMap(sf::RenderWindow &window);

    bool isWall_(int x, int y);

    void addFloor(int x, int y);

    void addWall(int x, int y);

    sf::Vector2f getCenter(){
        return {center.x * tileSize, center.y * tileSize};
    }

    void EntityMapCollision(int entityID);

    void attachListeners();

    static void EntityMapCollisionStatic(void *arg);
};


#endif //UNTITLED13_GAMEMAP_H
