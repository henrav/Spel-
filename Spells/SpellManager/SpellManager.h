//
// Created by Henrik Ravnborg on 2025-07-23.
//

#ifndef UNTITLED13_SPELLMANAGER_H
#define UNTITLED13_SPELLMANAGER_H
#pragma once
#include "../../Player/PlayerManager.h"

class SpellManager {
public:
    static void applySpellDMG(int playerID){
        std::cout<< "tjena from applySpelldmg" << std::endl;
        std::cout << PlayerManager::getPlayerByID(playerID).getPlayerId() << std::endl;
    }

    static void applySpellDebuff(){

    }
};


#endif //UNTITLED13_SPELLMANAGER_H
