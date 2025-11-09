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



using namespace std;


int main() {
    GameMap gameMap;
    EntityManager entityManager;
    ProjectileManager projectileManager;
    Engine::init(gameMap, entityManager, projectileManager);

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "test");
    window.setActive(true);


    Game game(window);
    game.run();




    return 0;
}


