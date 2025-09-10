//
// Created by Henrik Ravnborg on 2025-09-08.
//

#ifndef UNTITLED13_GAMEEVENTS_H
#define UNTITLED13_GAMEEVENTS_H

#endif //UNTITLED13_GAMEEVENTS_H

enum class DamageType : std::uint8_t {
    Physical,
    Magical,
    Pure,
};


struct DamageInstance {
    float amount{};
    DamageType type{DamageType::Magical};
};

enum class Resource : std::uint8_t {
    Mana,
    Health,
    Energy,
    None
};

enum class Event : std::uint8_t {
    UnitMoved,
    SpellCast,
    SpellHit,
    ProjectileCast,
    ProjectileHit,
    DamageTaken,
    DamageAvoided,
    DamageAbsorbed,
};

struct GameEvent{
    Event event ={};
};

struct MoveEventData{

};

struct MoveEvent : public GameEvent{

};

struct SpellCastEventData{
    int SpellID;

};

struct SpellCastEvent : public GameEvent{

};

struct ResourceCost {
    float amount = 0;
    Resource resource;

    ResourceCost(float amount, Resource resource) : amount(amount), resource(resource) {}
    ResourceCost() = default;
};