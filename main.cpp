extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <thread>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Entities/Managers/EntityManager.h"
#include "Entities/Managers/ProjectileManager.h"
#include "Map/Map.h"

std::unordered_map<int, std::shared_ptr<Entity>> EntityManager::entityList;
int EntityManager::entityID = 1;
std::unordered_map<int, std::shared_ptr<Projectile>> ProjectileManager::projectileList;
int ProjectileManager::projectileID = 1;

using namespace std;


int main() {

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "test");
    window.setActive(false);

/*
    Game game(window);
    game.run();
    */

Map map;
map.genMap();

    return 0;
}
