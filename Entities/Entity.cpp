//
// Created by Henrik Ravnborg on 2025-07-27.
//

#include "Entity.h"



bool Entity::isSpellImmune() const {
    return spellImmune;
}

void Entity::setSpellImmune(bool spellImmune) {
    Entity::spellImmune = spellImmune;
}

bool Entity::isTargetable() const {
    return targetable;
}

void Entity::setTargetable(bool targetable) {
    Entity::targetable = targetable;
}

int Entity::getId() const {
    return id;
}

void Entity::setId(int id) {
    Entity::id = id;
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

float Entity::getSpeed() {
    return speed;
}

void Entity::moveLeft(float dSpeed) {
    this->shape.move({-speed * dSpeed,0});
}

void Entity::moveUp(float dSpeed) {
    this->shape.move({0,-speed * dSpeed});
}

void Entity::moveDown(float dSpeed) {
    this->shape.move({0,speed * dSpeed});
}

void Entity::moveRight(float dSpeed) {
    this->shape.move({speed * dSpeed,0});
}


