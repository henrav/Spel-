//
// Created by Henrik Ravnborg on 2025-09-10.
//

#include "Map.h"
#include "iostream"
#include "random"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;



void Map::genMap() {
/*
    while (true){
        int length = randomNR();
        std::cout << length << std::endl;
    }
    */

    minkarta.resize(mapSize);
    for (int i = 0; i < mapSize; i++){
        minkarta[i].resize(mapSize);
        for (int a = 0; a < mapSize; a++){
            minkarta[i][a] = false;
            std::cout << (minkarta[i][a]);
        }
        printf("\n");
    }
    karta.resize(minkarta.size());
    for (int y = 0; y < karta.size(); y++){
        karta[y].resize(minkarta.size());
        for (int x = 0; x < karta.size(); x++){
            auto rectangle = sf::RectangleShape({blockSize, blockSize});
            rectangle.setPosition({static_cast<float>(x * posOff), static_cast<float>(y * posOff)});
            rectangle.setFillColor(sf::Color::White);
            karta[y][x] = rectangle;
        }
    }

    auto func= [](Direction direction){
        switch (direction) {

            case UP:
                std::cout << "up" << std::endl;
                break;
            case RIGHT:
                std::cout << "right"<< std::endl;
                break;
            case DOWN:
                std::cout << "down"<< std::endl;
                break;
            case LEFT:
                std::cout << "left"<< std::endl;
                break;
            case NONE:
                std::cout << "none" << std::endl;
                break;
        }
    };

    history.emplace_back(mapSize / 2, mapSize / 2, DOWN);
    for (int i = -(corridorWidth - 1) / 2; i < (corridorWidth - 1) / 2; i++ ){
        minkarta[mapSize / 2][mapSize + i / 2] = true;
    }
    bool backtrack = false;
    /*
    while (!history.empty()) {
            // Ny batch
            corridorWidth = 3;
            undoStack.clear();
            int digSteps = 0;
            int hits     = 0;
            constexpr int maxTry  = 15;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1,15);
            int random = dist6(rng);
            if (backtrack){
                for (int i = 0; i < maxTry; ++i) {
                    int chosenWidth = corridorWidth;
                    bool makeRoom = (random < 5);
                    if (makeRoom) {
                        chosenWidth = corridorWidth * GenRandomNR(2, 6);
                    }

                    potentialDig d = getPotDig(chosenWidth, makeRoom);
                    if (d.length == 0) break;

                    dig(d.direction, d.length, chosenWidth);
                    digSteps += d.length;
                    ++hits;

                    random = dist6(rng);
                }
                if (hits < maxTry) {
                    undoDigging(digSteps);
                    popBackHistory();
                }else{
                    backtrack = false;
                }
            }else{
                int chosenWidth = 0;
                potentialDig dd{};
                if (random < 5){
                    chosenWidth = corridorWidth * GenRandomNR(2, 6);
                    dd = getPotDig(chosenWidth, true);
                }else{
                    chosenWidth = corridorWidth;
                    dd = getPotDig(corridorWidth);
                }
                if (dd.length == 0){
                    popBackHistory();
                    backtrack = true;
                }else{
                    dig(dd.direction, dd.length, chosenWidth);
                    backtrack = false;
                }
            }

        std::this_thread::sleep_for(10ms);

    }
     */


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist15(1,20);
    int totalLength = 0;
    int length = 300;
    bool found = false;
    int a = 0;
    int maxRooms = 20;
    int minRooms = 4;
    while (true) {
        history.clear();
        undoStack.clear();
        history.emplace_back(mapSize / 2, mapSize / 2, DOWN );

        corridorWidth = 3;

        int digSteps  = 0;
        int hits      = 0;
        int rooms     = 0;

        const int minRoomGap = 25;
        int nextRoomAt = minRoomGap;

        for (int i = 0; i < length; ++i) {
            bool allowRoom = (digSteps >= nextRoomAt) && (rooms < maxRooms)
                             && (history.back().width == corridorWidth);

            int chosenWidth = corridorWidth;
            bool makeRoom   = false;
            bool randomWidth = false;

            if (allowRoom && dist15(rng) < 15) {
                if (dist15(rng) < 2){
                    chosenWidth = corridorWidth * GenRandomNR(3, 5);
                    makeRoom    = true;
                }else{
                    chosenWidth += GenRandomNR(1, 2);
                    randomWidth = true;
                }
            }

            potentialDig d = getPotDig(chosenWidth, makeRoom || randomWidth);
            if (d.length == 0) break;

            dig(d.direction, d.length, chosenWidth);

            digSteps += d.length;
            ++hits;

            if (makeRoom) {
                ++rooms;
                nextRoomAt = digSteps + GenRandomNR(minRoomGap, minRoomGap + 10);
            }
        }

        if (digSteps < length || rooms < minRooms) {
            undoDigging(digSteps);
            a--;
        } else {
            break;
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

void Map::undoDigging(int length){
    std::cout << undoStack.size() << std:: endl;
    for (auto it = undoStack.rbegin(); it != undoStack.rend(); ++it) {
        int y = it->first, x = it->second;
        if (minkarta[y][x]) {
            minkarta[y][x] = false;
            karta[y][x].setFillColor(sf::Color::White);
        }
    }
    undoStack.clear();
    for (int i = 0; i < length; ++i) {
        history.pop_back();
    }
}

potentialDig Map::getPotDig(int width, bool room) {
    Direction direction;
    int length;
    int tries = 0;
    do{
        direction = randomDirection();

        if (direction == oppositeDirection(history.back().direction) && direction == oppositeDirection(history[history.size() -1].direction)) {
            ++tries;
        }else {

            length = !room ? randomNR() : width * 2;

            if (!isDug(length, direction, width)) return {length, direction};
            ++tries;
        }

    } while (tries < 32);
    return {0, NONE};
}

void Map::dig(Direction direction, int length, int width) {
    int previousWidth = history.back().width;

    switch (direction) {
        case UP: {
            int centerXen = history.back().X
                            + (history.back().direction == RIGHT ? -previousWidth
                            : history.back().direction == LEFT  ? +previousWidth
                            : 0);
            int centerYen = history.back().direction == UP ? history.back().Y : history.back().Y - previousWidth;
            for (int i = 1; i <= length; ++i) {
                int centerY = centerYen - i;
                int centerX = centerXen ;
                for (int offset = -width; offset <= width; ++offset) {
                    if (!minkarta[centerY][centerX + offset]) {
                        minkarta[centerY][centerX + offset] = true;
                        karta[centerY][centerX + offset].setFillColor(sf::Color::Black);
                        undoStack.emplace_back(centerY, centerX + offset);
                    }
                }
                digPoint(centerY, centerX, UP, width);

            }
            break;
        }


        case RIGHT: {
            int centerYen = history.back().Y
                            + (history.back().direction == DOWN ? -previousWidth
                            : history.back().direction == UP   ? +previousWidth
                            : 0);
            int centerXen = history.back().direction == RIGHT ? history.back().X : history.back().X + previousWidth;
            for (int i = 1; i <= length; ++i) {
                int centerY = centerYen;
                int centerX =  centerXen + i;
                for (int offset = -width; offset <= width; ++offset) {
                    if (!minkarta[centerY + offset][centerX]) {
                    minkarta[centerY + offset][centerX] = true;
                    karta[centerY + offset][centerX].setFillColor(sf::Color::Black);
                    undoStack.emplace_back(centerY + offset, centerX);
                    }
                }
                digPoint(centerY, centerX, RIGHT, width);
            }
            break;
        }

        case DOWN: {
            int centerXen = history.back().X
                            + (history.back().direction == RIGHT ? -previousWidth
                            : history.back().direction == LEFT  ? +previousWidth
                            : 0);
            int centerYen = history.back().direction == DOWN ? history.back().Y : history.back().Y + previousWidth;
            for (int i = 1; i <= length; ++i) {
                int centerY =  centerYen + i ;
                int centerX = centerXen;
                for (int offset = -width; offset <= width; ++offset) {
                    if (!minkarta[centerY][centerX + offset]) {
                        minkarta[centerY][centerX + offset] = true;
                        karta[centerY][centerX + offset].setFillColor(sf::Color::Black);
                        undoStack.emplace_back(centerY, centerX + offset);
                    }
                }
                digPoint(centerY, centerX, DOWN, width);
            }
            break;
        }

        case LEFT: {

            int centerYen = history.back().Y
                            + (history.back().direction == UP   ? +previousWidth
                            : history.back().direction == DOWN ? -previousWidth
                            : 0);
            int centerXen = history.back().direction == LEFT ? history.back().X : history.back().X - previousWidth;
            for (int i = 1; i <= length; ++i) {
                int centerY = centerYen;
                int centerX =  centerXen - i;
                for (int offset = -width; offset <= width; ++offset) {
                    if (!minkarta[centerY + offset][centerX]) {
                        minkarta[centerY + offset][centerX] = true;
                        karta[centerY + offset][centerX].setFillColor(sf::Color::Black);
                        undoStack.emplace_back(centerY + offset, centerX);
                    }

                }
                digPoint(centerY, centerX, LEFT, width);
            }
            break;
        }

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

bool Map::isDug(int length, Direction direction, int width){
    int previousWidth = history.back().width;
    int padding = 2;
    Direction lastDirr = history.back().direction;
    int historyX = history.back().X;
    int historyY = history.back().Y;

    switch (direction) {
        case UP: {
            // flytta
            //
            //  xxxxx    xxxxx      xxxxx    xxxxx
            //  xxxxY -> xxYxx  OR  Yxxxx -> xxYxx
            //  xxxxx    xxxxx      xxxxx    xxxxx
            int centerXen = historyX
                            + (lastDirr == RIGHT ? -previousWidth
                            : lastDirr == LEFT  ? +previousWidth
                            : 0);
            // flytta
            //             Y
            //  xxxxx    xxxxx
            //  xxYxx -> xxxxx
            //  xxxxx    xxxxx
            int centerYen = lastDirr == UP ? historyY : historyY - previousWidth;
            for (int y = 1; y <= length + padding; y++){
                int nyY = centerYen - y;
                if (nyY < 0 || nyY >= mapSize) return true;
                for (int x = -(width + padding); x <= width + padding; x++){
                    int nyX = centerXen + x;
                    if (nyX < 0 || nyX >= mapSize) return true;
                    if (minkarta[nyY][nyX]) return true;
                }
            }
            return false;
        }


        case RIGHT: {
            int lastX = lastDirr == RIGHT ? historyX : historyX + previousWidth;
            int lastY = historyY
                        + (lastDirr == DOWN ? -previousWidth
                        : lastDirr == UP   ? +previousWidth
                        : 0);
            for (int x = 1; x <= length + padding; x++) {
                int nyX = lastX + x;
                if (nyX < 0 || nyX >= mapSize) return true;
                for (int y = -(width + padding); y <= width + padding; y++) {
                    if (lastY + y < 0 || lastY + y >= mapSize) return true;
                    if (minkarta[lastY + y][nyX]) return true;
                }
            }
            return false;
        }

        case DOWN: {
            int lastY = lastDirr == DOWN ? historyY : historyY + previousWidth;
            int lastX = historyX
                        + (lastDirr == RIGHT ? -previousWidth
                        : lastDirr == LEFT  ? +previousWidth
                        : 0);
            for (int y = 1; y <= length + padding; y++) {
                int nyY = lastY + y;
                if (nyY < 0 || nyY >= mapSize) return true;
                for (int x = -(width + padding); x <= width + padding; x++) {
                    int nyX = lastX + x;
                    if (nyX < 0 || nyX >= mapSize) return true;
                    if (minkarta[nyY][nyX]) return true;
                }
            }
            return false;
        }

        case LEFT: {
            int lastX = lastDirr == LEFT ? historyX : historyX - previousWidth;
            int lastY = historyY
                            + (lastDirr == UP   ? +previousWidth
                            : lastDirr == DOWN ? -previousWidth
                            : 0);
            for (int x = 1; x <= length + padding; x++) {
                int nyX = lastX - x;
                if (nyX < 0 || nyX >= mapSize) return true;
                for (int y = -(width + padding); y <= width + padding; y++) {
                    if (lastY + y < 0 || lastY + y >= mapSize) return true;
                    if (minkarta[lastY + y][nyX]) return true;
                }
            }
            return false;
        }


        case NONE:
            return true;
    }
    return false;
}

void Map::digPoint(int y, int x, Direction direction, int width){
    minkarta[y][x] = true;
    history.emplace_back(y, x, direction, width);
    karta[y][x].setFillColor(sf::Color::Red);
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
    std::uniform_int_distribution<std::mt19937::result_type> dist6(2,4);
    return dist6(rng);
}


int Map::GenRandomNR(int min, int max){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);
    return dist6(rng);
}

void Map::popBackHistory(){
    if (!history.empty()) {
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

std::vector<std::vector<bool>> Map::importMap() {
    return minkarta;
}

void Map::drawKarta(sf::RenderWindow& window) {
    for (int i = 0; i < karta.size(); i++){
        for (int a = 0; a < karta.size(); a++){
            window.draw(karta[i][a]);
        }
    }
}




