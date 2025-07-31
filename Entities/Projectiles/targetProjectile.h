//
// Created by Henrik Ravnborg on 2025-07-28.
//

#ifndef UNTITLED13_TARGETPROJECTILE_H
#define UNTITLED13_TARGETPROJECTILE_H


#include "../Projectile.h"

class targetProjectile : public Projectile{

public:

    /**
     * inits targetable Projectile constructor from Projectile.h
     *
     **/
    targetProjectile(float speed, float dmg, int ownerID, int targetID, sf::Vector2f startPos) : Projectile(speed, dmg, ownerID, targetID){
        this->shape.setPosition(startPos);
        this->shape.setSize({20, 20});
    };

    void update(float dt) override;

};


#endif //UNTITLED13_TARGETPROJECTILE_H
