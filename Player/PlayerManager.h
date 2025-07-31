//
// Created by Henrik Ravnborg on 2025-07-23.
//
#ifndef UNTITLED13_PLAYERMANAGER_H
#define UNTITLED13_PLAYERMANAGER_H
#pragma once
#include "Player.h"
#include "iostream"

class PlayerManager {
private:
    static std::unordered_map<int, Player> players;
    static int id;
public:


    static Player getPlayerByID(int playerID){
        return players.at(playerID);
    }

    static const void addPlayer(Player &player){
    player.setPlayerId(id);
    players.insert({id, player});
    id++;
    }

    static int getManagerSize(){
    return players.size() +1;
    }




};



#endif //UNTITLED13_PLAYERMANAGER_H
