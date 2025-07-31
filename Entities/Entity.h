//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_ENTITY_H
#define UNTITLED13_ENTITY_H


#include "Drawable.h"

class Entity : public Drawable{
protected:
    int id;

    bool spellImmune;

    bool targetable;

    float speed;

    int health = 100;

    int mana;


public:
    int getId() const;

    void setId(int id);

    bool isSpellImmune() const;

    void setSpellImmune(bool spellImmune);

    bool isTargetable() const;

    void setTargetable(bool targetable);

    Entity(float size, float posx, float posy, float speed){
        this->shape.setSize({size, size});
        this->shape.setPosition({posx, posy});
        this->speed = speed;
    }

    void setSpeed(float speed);

    float getSpeed();

    void moveLeft(float dSpeed);
    void moveRight(float dSpeed);
    void moveUp(float dSpeed);
    void moveDown(float dSpeed);


    int getHealth();

    void setHealth(int value);

    int getMana();

    void setMana(int value);






};


#endif //UNTITLED13_ENTITY_H
