//
// Created by Henrik Ravnborg on 2025-07-27.
//

#include "Projectile.h"

int Projectile::getId() const {
    return id;
}

void Projectile::setId(int idd) {
    this->id = idd;
}

int Projectile::getTargetId() const {
    return targetID;
}

void Projectile::setTargetId(int targetId) {
    targetID = targetId;
}

int Projectile::getOwnerId() const {
    return ownerID;
}

void Projectile::setOwnerId(int ownerId) {
    ownerID = ownerId;
}

const sf::Vector2f &Projectile::getTargetPos() const {
    return targetPos;
}

void Projectile::setTargetPos(const sf::Vector2f &targetPos) {
    Projectile::targetPos = targetPos;
}

void Projectile::setDead(bool value) {
    dead = value;
}

bool Projectile::getDead() {
    return dead;
}


