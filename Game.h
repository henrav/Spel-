//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_GAME_H
#define UNTITLED13_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <thread>
#include "Entities/Managers/ProjectileManager.h"
#include "Entities/Managers/EntityManager.h"

class Game {
    sf::RenderWindow& window;

    const float dt      = 1.f / 120.f;
    float       acc     = 0.f;
    sf::Clock   clock;
public:
    void draw();

    void run();

    void RenderThread();

    Game(sf::RenderWindow &window) : window(window){
    }

};


#endif //UNTITLED13_GAME_H
