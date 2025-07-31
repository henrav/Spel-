//
// Created by Henrik Ravnborg on 2025-07-27.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "Game.h"


void Game::run() {
    auto& projectile = ProjectileManager::addProjectile<targetProjectile>(500 ,10, 10, 1, sf::Vector2f{600, 20});

    auto& entity1 = EntityManager::addEntity<Entity>(10, 200, 10, 30);
    auto& entity = EntityManager::addEntity<Entity>(10, 200, 10, 300);
    entity.setSize({20, 20});

    window.setActive(false);
    std:: thread thread(&Game::RenderThread, this);


    while (window.isOpen()){
        acc += clock.restart().asSeconds();
        while (acc >= dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){
                entity.moveUp(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)){
                entity.moveDown(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)){
                entity.moveLeft(dt);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)){
                entity.moveRight(dt);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)){
                ProjectileManager::addProjectile<targetProjectile>(500 ,10, 10, 1, sf::Vector2f {entity.getShape().getPosition().x, entity.getShape().getPosition().y,});

                std::cout << entity.getShape().getPosition().x << "y" << entity.getShape().getPosition().y << std::endl;
            }
            ProjectileManager::update(dt);
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
        ProjectileManager::drawProjectiles(window);
        EntityManager::drawEntities(window);
        window.display();
    }
}