//
// Created by Henrik Ravnborg on 2025-07-23.
//

#include "Player.h"


int Player::getPosX() const {
    return posX;
}

void Player::setPosX(int posX) {
    Player::posX = posX;
}

int Player::getPosY() const {
    return posY;
}

void Player::setPosY(int posY) {
    Player::posY = posY;
}

int Player::getPlayerId() const {
    return playerID;
}

void Player::setPlayerId(int playerId) {
    playerID = playerId;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int health) {
    Player::health = health;
}

int Player::getMana() const {
    return mana;
}

void Player::setMana(int mana) {
    Player::mana = mana;
}

Player::Player(int posX, int posY, int health, int mana) : posX(posX), posY(posY),
                                                                         health(health), mana(mana) {

}
