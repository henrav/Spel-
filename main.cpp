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
    window.setActive(true);

/*
    Game game(window);
    game.run();
    */

Map map;
    std::thread thread([&map]() {
        map.genMap();
    });
    thread.detach();
    sf::View view;
    float centerX = static_cast<float>(map.getSize()) * map.getOff() * 0.5f;
    float centerY = static_cast<float>(map.getSize()) * map.getOff() * 0.5f;
    view.setCenter({centerX, centerY});
    view.setSize({static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    window.setView(view);

// zoom state
    float zoom = 1.f;
    const float zoomStep = 1.1f;   // 10% per hack
    const float minZoom  = 0.1f;
    const float maxZoom  = 8.f;
    std::this_thread::sleep_for(100ms);

// pan state
    bool panning = false;
    sf::Vector2i panStart{0,0};

    while (window.isOpen()) {
        while (const std::optional ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();

            // fönster-resize
            if (auto* e = ev->getIf<sf::Event::Resized>()) {
                view.setSize({static_cast<float>(e->size.x), static_cast<float>(e->size.y)});
                window.setView(view);
            }

            // zoom med scrollhjul (zoomar mot muspekaren)
            if (auto* e = ev->getIf<sf::Event::MouseWheelScrolled>()) {
                // zooma mot muspekaren
                sf::Vector2i pixel = e->position;
                sf::Vector2f before = window.mapPixelToCoords(pixel, view);

                // Gör riktning robust: delta>0 -> zooma in, delta<0 -> zooma ut (även på mac)
                // Nyckeln: pow(zoomStep, -delta)
                float f = std::pow(zoomStep, -e->delta);

                float newZoom = std::clamp(zoom * f, minZoom, maxZoom);
                float apply   = newZoom / zoom;   // det vi faktiskt ska applicera på view
                zoom = newZoom;

                view.zoom(apply);

                // håll muspekaren “still” i världen
                sf::Vector2f after = window.mapPixelToCoords(pixel, view);
                view.move(before - after);

                window.setView(view);
            }

            // starta pan med höger musknapp
            if (auto* e = ev->getIf<sf::Event::MouseButtonPressed>()) {
                if (e->button == sf::Mouse::Button::Right) {
                    panning = true;
                    panStart = e->position;
                }
            }
            // släpp pan
            if (auto* e = ev->getIf<sf::Event::MouseButtonReleased>()) {
                if (e->button == sf::Mouse::Button::Right) panning = false;
            }
            // pan medan du drar
            if (auto* e = ev->getIf<sf::Event::MouseMoved>()) {
                if (panning) {
                    sf::Vector2i now = e->position;
                    sf::Vector2f before = window.mapPixelToCoords(panStart, view);
                    sf::Vector2f after  = window.mapPixelToCoords(now, view);
                    view.move(before - after);
                    panStart = now;
                    window.setView(view);
                }
            }
        }

        window.clear();
        window.setView(view);  // se till att använda senaste view innan draw
        map.drawKarta(window);
        window.display();
    }

    return 0;
}


