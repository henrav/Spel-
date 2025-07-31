//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_PROJECTILE_H
#define UNTITLED13_PROJECTILE_H

#include <iostream>
#include "Entity.h"


class Projectile : public Drawable {

protected:

    //projectileID/selfID
    int id;

    float dmg;

    float speed;

    //targetID if it has target
    int targetID;

    //ownerID
    int ownerID;

    //x,y pos if vector projectile
    sf::Vector2f targetPos;

    bool dead;

public:



    /** for targetable Projectiles
     *  @param id = id for this projectile
     *  @param speed = speed for this projectile
     *  @param dmg = dmg for this projectile
     *  @param ownerID = owner for this projectile
     *  @param targetID = target id for this projectile
     * **/
    Projectile(float speed,
               float dmg,
               int ownerID,
               int targetID) :
               speed(speed),
               dmg(dmg),
               ownerID(ownerID),
               targetID(targetID){
    };

    /** for vector Projectiles
     *  for targetable Projectiles
     *  @param id = id for this projectile
     *  @param speed = speed for this projectile
     *  @param dmg = dmg for this projectile
     *  @param ownerID = owner for this projectile
     *  @param finalPos = x y coords target for this projectile
     * **/
    Projectile(float speed,
               float dmg,
               int ownerID,
               sf::Vector2i finalPos) :
               speed(speed),
               dmg(dmg),
               ownerID(ownerID),
               targetPos(finalPos){
       ;
    };

    int getTargetId() const;

    void setTargetId(int targetId);

    int getOwnerId() const;

    void setOwnerId(int ownerId);

    const sf::Vector2f &getTargetPos() const;

    void setTargetPos(const sf::Vector2f &targetPos);

    float getDmg() const {
        return dmg;
    }

    void setDmg(float d) {
        Projectile::dmg = d;
    }

    float getSpeed() const {
        return speed;
    }

    void setSpeed(float s) {
        Projectile::speed = s;
    }

    int getId() const;

    void setId(int id);

    void setDead(bool value);

    bool getDead();

    virtual void update(float dt) = 0;


};


#endif //UNTITLED13_PROJECTILE_H
