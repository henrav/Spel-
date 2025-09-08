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

struct EngineAPI; // forward
struct Unit { int id = 0; };
struct ProjectileAPI;

enum DamageType{
    PHSYICAL,
    MAGICAL,
    PURE,
};


struct DamageInstance{
    float amount = 0;
    DamageType damageType = MAGICAL;

    DamageInstance(float amount, DamageType damageType) : amount(amount), damageType(damageType) {};
    DamageInstance();
};

enum Resource{
    MANA,
    HEALTH,
    ENERGY,
    NONE
};
/**
 * @brief Represents the cost of a resource required to perform an action, such as casting a spell.
 *
 * @param amount The quantity of the resource required.
 * @param resource The type of resource (e.g., MANA, HEALTH, ENERGY).
 */
struct ResourceCost {
    float amount = 0;
    Resource resource = NONE;

    ResourceCost(float amount, Resource resource) : amount(amount), resource(resource) {}
    ResourceCost() = default;
};


struct Spell{
    int ownerID = 0;
    float cooldown = 0;
    sf::Clock clock;
    ResourceCost resourceCost;
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


Spell makeTestSpell(int ownerID);


