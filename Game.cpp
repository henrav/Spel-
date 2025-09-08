//
// Created by Henrik Ravnborg on 2025-07-27.
//
#include <sol/sol.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Game.h"
#include "Spells/Spells/Spells.h"
#include "Entities/Entity.h"
#include <thread>

Spell myTestSpell(int ownerID);

void Game::run() {

    auto& player = GameEngineAPI::addEntity<Entity>(10, 200, 10, 300);
    player.setSize({20, 20});


    window.setActive(false);
    std:: thread thread(&Game::RenderThread, this);
    auto spell = myTestSpell(player.getId());


    while (window.isOpen()){
        acc += clock.restart().asSeconds();
        while (acc >= dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){
                player.moveUp(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)){
                player.moveDown(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)){
                player.moveLeft(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)){
                player.moveRight(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q)){
                player.moveRight(dt);
                spell.onCast();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)){
                spell.onHit();
            }
            GameEngineAPI::update(0.16);
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

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        GameEngineAPI::draw(window);
        window.display();
    }
}