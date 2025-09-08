//
// Created by Henrik Ravnborg on 2025-07-23.
//

#ifndef UNTITLED13_PLAYER_H
#define UNTITLED13_PLAYER_H

#include <iostream>
using namespace std;

class Player {
private:
    int playerID = 0;
    int health;
    int mana;
    int posY;
    int posX;
    vector<char> keyBindings;

public:
    Player(int posX, int posY, int health, int mana);

    int getPosX() const;

    void setPosX(int posX);

    int getPosY() const;

    void setPosY(int posY);

    int getPlayerId() const;

    void setPlayerId(int playerId);

    int getHealth() const;

    void setHealth(int health);

    int getMana() const;

    void setMana(int mana);

    void changeSpellBinding(int pos, char value);

};


#endif //UNTITLED13_PLAYER_H
