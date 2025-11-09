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
    std::cout<< "pos x: " << this->shape.getPosition().x << "pos x: " << this->shape.getPosition().y << std::endl;

}

void Entity::moveUp(float dSpeed) {
    this->shape.move({0,-speed * dSpeed});
    std::cout<< "pos x: " << this->shape.getPosition().x << "pos x: " << this->shape.getPosition().y << std::endl;
}

void Entity::moveDown(float dSpeed) {
    this->shape.move({0,speed * dSpeed});
    std::cout<< "pos x: " << this->shape.getPosition().x << "pos x: " << this->shape.getPosition().y << std::endl;

}

void Entity::moveRight(float dSpeed) {
    this->shape.move({speed * dSpeed,0});
    std::cout<< "pos x: " << this->shape.getPosition().x << "pos x: " << this->shape.getPosition().y << std::endl;

}

void Entity::setMana(int value) {
    this->mana = value;
}

void Entity::setHealth(int value) {
    this->health = value;
}

int Entity::getHealth() {
    return this->health;
}

int Entity::getMana() {
    return this->health;
}




