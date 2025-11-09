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
    int length = 1000;
    bool found = false;
    int maxRooms = 5;
    int minRooms = 5;
    int it = 0;
    corridorWidth = 5;

    int digSteps  = 0;
    int rooms     = 0;
    int tries = 0;
    int backtrackDepth = 1;
    const int maxBacktrackDepth = 64;
    const int minRoomGap = 100;
    int nextRoomAt = minRoomGap;
    bool back = false;
    std::vector<int> roomEndPos;
    roomEndPos.reserve(maxRooms + 4);
    history.emplace_back(mapSize / 2, mapSize / 2, DOWN);
    dig(DOWN, 30, 15);

    starty = mapSize / 2 + 15;
    startx = mapSize / 2;

    while (rooms < maxRooms) {

        bool allowRoom = (digSteps >= nextRoomAt)
                         && (history.back().width < corridorWidth +3);
        if (rooms == 0){
            allowRoom = true;
        }
        int chosenWidth  = corridorWidth;
        bool makeRoom    = false;
        bool randomWidth = false;

        if (allowRoom) {
            if (dist15(rng) < 10){
                chosenWidth = corridorWidth * GenRandomNR(3, 4);
                makeRoom    = true;
            }
        }

        if (dist15(rng) <= 15) {
            chosenWidth += GenRandomNR(1, 2);
            randomWidth  = true;
        }

        potentialDig d = getPotDig(chosenWidth, makeRoom || randomWidth);
        if (d.length == 0) {
            while (!history.empty()){
                bool lastWasRoom = history.back().width >= corridorWidth*2;
                int lastLength = history.back().length;
                it       -= history.back().length;
                undoDigging();
                if (!lastWasRoom){
                    nextRoomAt -= lastLength;
                }else{
                    rooms--;
                }
                allowRoom = (digSteps >= nextRoomAt)
                                 && (history.back().width < corridorWidth +3);
                chosenWidth  = corridorWidth;
                makeRoom    = false;
                randomWidth = false;

                if (allowRoom) {
                    if (dist15(rng) < 10){
                        chosenWidth = corridorWidth * GenRandomNR(3, 4);
                        makeRoom    = true;
                    }
                }

                if (dist15(rng) <= 15) {
                    chosenWidth += GenRandomNR(1, 2);
                    randomWidth  = true;
                }

                d = getPotDig(chosenWidth, (makeRoom || randomWidth));
                if (d.length != 0) break;
                tries++;
            }
        }
        if (d.length != 0){
            dig(d.direction, d.length, chosenWidth);

            digSteps += d.length;
            if (makeRoom) {
                roomEndPos.push_back(digSteps);
                nextRoomAt =  d.length + GenRandomNR(minRoomGap, minRoomGap + 50);
                ++rooms;
            }
            it += d.length;
            back = false;
        }




       std::this_thread::sleep_for(100ms);






        std::cout << it << std::endl;


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

void Map::undoDigging() {
    if (history.empty()) return;
    Direction d = history.back().direction;
    int halfWidth = history.back().width;
    int steps     = history.back().length;

    long long cellsToRevert = 1LL * steps * (2*halfWidth + 1);

    int n = (int)std::min<long long>(cellsToRevert, undoStack.size());

    while (n-- > 0 && !undoStack.empty()) {
        auto [y, x] = undoStack.back();
        undoStack.pop_back();
        if (y >= 0 && x >= 0 && minkarta[y][x]) {
            minkarta[y][x] = false;
            karta[y][x].setFillColor(sf::Color::White);
        }
    }

    for (int i = 0; i < steps && !history.empty(); ++i) {
        history.pop_back();
    }
    history.back().markTried(d);
}

potentialDig Map::getPotDig(int width, bool room) {
    Direction direction;
    int length;
    int tries = 0;
    do{
        direction = randomDirection();

        if (direction == oppositeDirection(history.back().direction) ){tries++; continue;}
        if (history.back().isTried(direction)){tries++; continue;}


            length = !room ? randomNR() : width * 2;

            if (!isDug(length, direction, width)) return {length, direction};
        history.back().markTried(direction);
            ++tries;

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
                digPoint(centerY, centerX, UP, width, length);

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
                digPoint(centerY, centerX, RIGHT, width, length);

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
                digPoint(centerY, centerX, DOWN, width, length);
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
                digPoint(centerY, centerX, LEFT, width, length);

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
    int padding = 5;
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

void Map::digPoint(int y, int x, Direction direction, int width, int length) {
    minkarta[y][x] = true;
    history.emplace_back(y, x, direction, width, length);
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
    std::uniform_int_distribution<std::mt19937::result_type> dist6(3,4);
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




