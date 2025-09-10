//
// Created by Henrik Ravnborg on 2025-09-10.
//

#include "Map.h"
#include "iostream"
#include "random"


void Map::genMap() {
    minkarta.resize(mapSize);
    for (int i = 0; i < mapSize; i++){
        minkarta[i].resize(mapSize);
        for (int a = 0; a < mapSize; a++){
            minkarta[i][a] = false;
            std::cout << (minkarta[i][a]);
        }
        printf("\n");
    }
    while (mazeLength >= 0){
        if (history.empty()){
            minkarta[mapSize - 1][0] = true;
            history.emplace_back(mapSize - 1, 0, NONE);
        }else{
            Direction direction;
            int length;
            int tries = 0;


            do {
                direction = randomDirection();
                if (direction == oppositeDirection(history.back().direction)) {
                    ++tries;
                    continue;
                }
                length = randomNR();
                if (!isDug(length, direction)) break;
                ++tries;
            } while (tries < 32);

            if (tries >= 32) {
                popBackHistory();
                if (history.empty()) break;
                continue;
            }
            dig(direction, length);
        }
    }

    system("cls");
    for (int i = 0; i < mapSize; i++){
        for (int a = 0; a < mapSize; a++){
            if (minkarta[i][a]){
                printf(" ");
            }else{
                printf("*");
            }
        }
        printf("\n");
    }




}

void Map::dig(Direction direction, int length) {
    switch (direction) {
        case UP:
            for (int i = 0; i < length; i++){
               int lastY = history.back().Y - 1;
               int lastX = history.back().X;
               digPoint(lastY, lastX, UP);
            }
            break;
        case RIGHT:
            for (int i = 0; i < length; i++){
                int lastY = history.back().Y;
                int lastX = history.back().X + 1;
                digPoint(lastY, lastX, RIGHT);
            }
            break;
        case DOWN:
            for (int i = 0; i < length; i++){
                int lastY = history.back().Y + 1;
                int lastX = history.back().X;
                digPoint(lastY, lastX, UP);
            }
            break;
        case LEFT:
            for (int i = 0; i < length; i++){
                int lastY = history.back().Y;
                int lastX = history.back().X - 1;
                digPoint(lastY, lastX, RIGHT);
            }
            break;
        case NONE:
            break;
    }
}

Direction Map::oppositeDirection(Direction direction){
    switch (direction) {
        case UP:
            return DOWN;
        case RIGHT:
            return LEFT;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case NONE:
            return NONE;
    }
}

bool Map::isDug(int length, Direction direction){
    switch (direction) {
        case UP:
            for (int i = 1; i < length + 4; i++){
                int lastY = history.back().Y - i;
                int lastX = history.back().X;
                if (lastY <= 0){
                    return true;
                }
                if (minkarta[lastY][lastX]){
                    return true;
                }
            }
            return false;
        case RIGHT:
            for (int i = 1; i < length + 4; i++){
                int lastY = history.back().Y;
                int lastX = history.back().X + i;
                if (lastX >= mapSize){
                    return true;
                }
                if (minkarta[lastY][lastX]){
                    return true;
                }
            }
            return false;
        case DOWN:
            for (int i = 1; i < length + 4; i++){
                int lastY = history.back().Y + i;
                int lastX = history.back().X;
                if (lastY >= mapSize){
                    return true;
                }
                if (minkarta[lastY][lastX]){
                    return true;
                }
            }
            return false;
        case LEFT:
            for (int i = 1; i < length + 4; i++){
                int lastY = history.back().Y;
                int lastX = history.back().X - i;
                if (lastX <= 0){
                    return true;
                }
                if (minkarta[lastY][lastX]){
                    return true;
                }
            }
            return false;
        case NONE:
            return true;
    }
    return false;
}

void Map::digPoint(int y, int x, Direction direction){
    minkarta[y][x] = true;
    history.emplace_back(y, x, direction);
    mazeLength--;
}

Direction Map::randomDirection(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,4);
    return getDirection(dist6(rng));
}

int Map::randomNR(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(3,4);
    return dist6(rng);
}

void Map::popBackHistory(){
    if (!history.empty()) {
        History history1 = history.back();
        minkarta[history1.Y][history1.X] = false;
        history.pop_back();
    }
}

bool Map::isOutOfBounds(int Y, int X) const{
    if (Y > mapSize || Y < mapSize || X > mapSize || X < mapSize) return true;
    return false;
}

Direction Map::getDirection(int value){
    switch (value) {
        case 1:
            return UP;
        case 2:
            return RIGHT;
        case 3:
            return DOWN;
        case 4:
            return LEFT;
        default:
            return NONE;
    }
}




