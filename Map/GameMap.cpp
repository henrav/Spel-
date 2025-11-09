//
// Created by Henrik Ravnborg on 2025-10-14.
//

#include "GameMap.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include "../Entities/Managers/GameEngineAPI.h"
#include "../Entities/Entity.h"
#include "../Bus/EventHandler.h"
using namespace std;
using namespace handler;



GameMap::GameMap() {
    assert(tileSize > 0 && "tileSize must be set before loadMap()");
    std::cout << "tileSize=" << tileSize << "\n";
    Map maps;
    maps.genMap();
    this->mapData = maps.getMap();
    loadMap();
    this->center = maps.getstartPos();
    size_t maxTilesToPrint = (map.size() < 5) ? map.size() : 5;

    for (size_t i = 0; i < maxTilesToPrint; ++i) {
        auto gb = map[i].getGlobalBounds();
        std::cout << "tile[" << i << "] pos=("
                  << gb.position.x << "," << gb.position.y
                  << ") size=("
                  << gb.size.x << "x" << gb.size.y << ")\n";
    }
    std::cout<<"tjen123a" << endl;
}

void GameMap::loadMap() {

    int minArray[3][3] = {
            {-1,0,1},
            {-1,0,1},
    };

    for (int y = 0; y < mapData.size(); y++){
        for(int x = 0; x < mapData.size(); x++ ){
            if (y > mapData.size() - 2 || y < 2 || x > mapData[0].size() - 2 || x < 2) {
                continue;
            }
            if (mapData[y][x]){
                addFloor(x, y);
                ground.emplace_back(GROUND, x, y);
                cout <<"added flor" << "x: " << x << "y: " << y << endl;
            }else{
                if (isWall_(x, y)){
                    addWall(x, y);
                    walls.emplace_back(WALL, x, y);
                    cout <<"added wall" << "x: " << x << "y: " << y << endl;
                }
            }
        }
    }
}




/**
 * simple check to see if point on map "touches" something "true", if so then its a wall.
 * @param x xpos
 * @param y ypos
 * @return
 */
bool GameMap::isWall_(int x, int y) {
    if (mapData[y][x]) return false;

    for (int Y = -1; Y <= 1; Y++){
        for (int X = -1; X <= 1; X++){
            if (mapData[y + Y][x + X]){
                return true;
            }
        }
    }
    return false;
}

void GameMap::addFloor(int x, int y) {
    sf::RectangleShape floor;
    floor.setSize({static_cast<float>(tileSize), static_cast<float>(tileSize)});
    floor.setPosition({x*(float)tileSize, y*(float)tileSize});
    floor.setFillColor(sf::Color(0, 255, 255, 100)); // alpha 100
    map.emplace_back(floor);
}

void GameMap::addWall(int x, int y){
    sf::RectangleShape wall;
    wall.setSize({static_cast<float>(tileSize), static_cast<float>(tileSize)});
    wall.setPosition({x*(float)tileSize, y*(float)tileSize});
    wall.setFillColor(sf::Color(255, 0, 0, 100));    // alpha 100
    map.emplace_back(wall);
}



void GameMap::drawMap(sf::RenderWindow& window){
    for (const auto & i : map){
        window.draw(i);

    }
}

void GameMap::EntityMapCollisionStatic(void *arg){

}
void GameMap::EntityMapCollision(int entityID){
    Entity& entity = Engine::getEntity(entityID);

    for (auto& it : walls){

        const float playerx = entity.shape.getPosition().x;
        const float playery = entity.shape.getPosition().y;
        // Scale wall position using tileSize
        const float wallx = it.x * tileSize;
        const float wally = it.y * tileSize;

// Calculate deltas
        const float deltaX = std::abs(playerx - wallx);
        const float deltaY = std::abs(playery - wally);

        if (deltaX < tileSize && deltaY < tileSize) {
            std::cout << "Collision detected at (" << wallx << ", " << wally << ")\n";
        }
    }

}

void GameMap::attachListeners() {
    Bus().subscribe<int>(handler::event::moveEvent, [this](const int& id){
        this->EntityMapCollision(id);
    });
}

