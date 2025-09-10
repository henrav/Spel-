//
// Created by Henrik Ravnborg on 2025-09-10.
//

#ifndef UNTITLED13_MAP_H
#define UNTITLED13_MAP_H
#include "iostream"

enum Direction{
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
    NONE = 5
};

struct History{
    Direction direction = NONE;
    int X;
    int Y;

    History(int y, int x, Direction direction1) : Y(y), X(x), direction(direction1){};
    History(int y, int x) : Y(y), X(x){};

};

class Map {
private:
    std::vector<History> history;
    std::vector<std::vector<bool>> minkarta;
    int mapSize = 50;
    int mazeLength = 400;

public:
    void genMap();

    static Direction getDirection(int value);

    void popBackHistory();

    bool isOutOfBounds(int Y, int X) const;

    Direction randomDirection();

    void digPoint(int y, int x, Direction direction);

    bool isDug(int y, int x);

    int randomNR();

    bool isDug(int length, Direction direction);

    Direction oppositeDirection(Direction direction);

    void dig(Direction direction, int length);
};


#endif //UNTITLED13_MAP_H
