//
// Created by Henrik Ravnborg on 2025-07-27.
//
#include <sol/sol.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Game.h"
#include "Spells/Spells/Spells.h"
#include "Entities/Entity.h"
#include "Map/Map.h"
#include <thread>
#include "Map/GameMap.h"
#include "Bus/EventHandler.h"
using namespace handler;

Spell myTestSpell(int ownerID);

void Game::run() {

    player = &Engine::addEntity<Entity>(10, 200, 10, 300);
    player->setSize({20, 20});
    std::cout << Engine::getMapCenter().x << endl;
    cout << Engine::getMapCenter().y << endl;
    Engine::setUnitPos(Engine::getMapCenter(), player->getId());
    window.setActive(false);
    std:: thread thread(&Game::RenderThread, this);
    auto spell = myTestSpell(player->getId());

    sf::View camera(window.getDefaultView());
    while (window.isOpen()){
        acc += clock.restart().asSeconds();
        while (acc >= dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){
                player->moveUp(dt);
                Bus().emit(handler::event::moveEvent, 1);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)){
                player->moveDown(dt);
                Bus().emit(handler::event::moveEvent, 1);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)){
                player->moveLeft(dt);
                Bus().emit(handler::event::moveEvent, 1);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)){
                player->moveRight(dt);
                Bus().emit(handler::event::moveEvent, 1);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q)){
                spell.onCast();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z)) {
                camera.zoom(0.99f); // zoom in smoothly
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X)) {
                camera.zoom(1.01f); // zoom out smoothly
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)){
                spell.onHit();
            }
            Engine::update(0.16);
            acc -= dt;
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }


    }
    thread.join();
}


void Game::RenderThread() {
    window.setActive(true);

    sf::View camera(window.getDefaultView());
    camera.zoom(2.0f); // if you want zoom-out

    while (window.isOpen()) {
        // center camera on player each frame
        const auto playerPos = Engine::getUnitPos(player->getId());
        camera.setCenter(playerPos);
        window.setView(camera);
        window.clear();
        Engine::draw(window);
        window.display();
    }
}