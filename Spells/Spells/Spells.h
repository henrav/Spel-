//
// Created by Henrik Ravnborg on 2025-09-06.
//

#ifndef UNTITLED13_SPELLS_H
#define UNTITLED13_SPELLS_H

#endif //UNTITLED13_SPELLS_H
#pragma once
#include "iostream"
#include "any"
#include <SFML/System.hpp>
#include <functional>


struct Unit { int id = 0; };
struct ProjectileAPI;





struct Spell{
    int ownerID = 0;
    float cooldown = 0;
    sf::Clock clock;

    std::function<void()> onCast = [](){std::cout<<"onCast not implemented" << std::endl;};
    std::function<void()> onHit = [](){std::cout<<"On hit not implemented" << std::endl;};

    template<typename T>
    T& state(const std::string& key, T initialValue = {}) {
        auto& slot = variables[key];
        if (!slot.has_value()) slot = initialValue;
        return *std::any_cast<T>(&slot);
    }

private:
    std::unordered_map<std::string, std::any> variables;
};




