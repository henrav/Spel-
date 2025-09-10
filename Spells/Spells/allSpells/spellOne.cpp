//
// Created by Henrik Ravnborg on 2025-09-06.
//
#include "../Spells.h"
#include "../../../Entities/Managers/GameEngineAPI.h"
#include "../../../Entities/Projectiles/Projectiles.h"
#include <memory>
#include <cmath>

Spell myTestSpell(int ownerID){

    struct spellVariables{
        int hits = 0;
        int pHit= 0;
        int pUpdate = 0;
        int pColl = 0;
    };

    auto variables = std::make_shared<spellVariables>();


    Spell s;
    s.ownerID = ownerID;
    s.cooldown = 5;

    s.onHit = [variables](){
        //TODO
    };

    s.onCast = [variables](){
        auto p = std::make_shared<Projectile>();
        GameEngineAPI::spawnProjectile(p);
        p->speed = 1;
        p->targetID = 1;
        p->onHit = [variables](Projectile& self){

        };

        p->update = [variables](Projectile& self) {
            std::cout<<"tjena"<<std::endl;
            std::cout<<"pos X: " << self.getShape().getPosition().x << std::endl;
            sf::Vector2f d = GameEngineAPI::getUnitPos(self.targetID) - self.getShape().getPosition();
            float len2 = d.x*d.x + d.y*d.y;
            if (len2 > 0.0001f) {
                float len = std::sqrt(len2);
                sf::Vector2f step = (self.speed / len) * d;
                self.moveShape(step);
            }

        };

        p->onCollision = [variables](Projectile& self){
            //TODO if locationTargetable
            //deal damage and continue moving untill reached end
            //if unit target do nothing unless collision with target
        };
    };


    return s;
}
