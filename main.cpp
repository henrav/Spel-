extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <thread>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Entities/Projectile.h"
#include "Player/PlayerManager.h"
#include "Spells/SpellManager/SpellManager.h"
#include "Entities/Managers/EntityManager.h"
#include "Entities/Managers/ProjectileManager.h"

std::unordered_map<int, Player> PlayerManager::players;
int PlayerManager::id = 1;
std::unordered_map<int, std::unique_ptr<Entity>> EntityManager::entityList;
int EntityManager::entityID = 1;
std::unordered_map<int, std::unique_ptr<Projectile>> ProjectileManager::projectileList;
int ProjectileManager::projectileID = 1;

using namespace std;


int main() {

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "test");
    window.setActive(false);


    Game game(window);
    game.run();


    if (luaL_dostring(L, "print('Hello from Lua!')")) {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
    }

    lua_close(L);                       // Clean up
    return 0;
}
