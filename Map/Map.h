//
// Created by Henrik Ravnborg on 2025-09-10.
//

#ifndef UNTITLED13_MAP_H
#define UNTITLED13_MAP_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
    int width;

    History(int y, int x, Direction direction1, int width) : Y(y), X(x), direction(direction1), width(width){};
    History(int y, int x, Direction direction1) : Y(y), X(x), direction(direction1){};
    History(int y, int x) : Y(y), X(x){};

};

struct potentialDig{
    int length;
    Direction direction;
};
struct DugBatch {
    std::vector<std::pair<int, int>> cells;
    int steps = 0;
};
class Map {
private:
    std::vector<History> history;
    std::vector<std::vector<bool>> minkarta;
    int mapSize = 200;
    int mazeLength = 30;
    std::vector<std::vector<sf::RectangleShape>> karta;
    float blockSize = 5;
    float posOff = 6;
    sf::Clock clock;
    int corridorWidth = 4;
    int lastCorridorWidth= 0;
    std::vector<std::pair<int, int>> undoStack;

public:

    void undoDigging(int length);
    void genMap();

    static Direction getDirection(int value);

    void popBackHistory();

    bool isOutOfBounds(int Y, int X) const;

    Direction randomDirection();

    void digPoint(int y, int x, Direction direction, int width);

    bool isDug(int y, int x);

    int randomNR();

    bool isDug(int length, Direction direction, int width);

    Direction oppositeDirection(Direction direction);

    void dig(Direction direction, int length, int width);

    std::vector<std::vector<bool>> importMap();

    void drawKarta(sf::RenderWindow& window);

    float getSize() const{
        return static_cast<float>(mapSize);
    }

    float getOff(){
        return static_cast<float>(posOff);
    }

    potentialDig getPotDig(int width, bool b = false);

    int GenRandomNR(int min, int max);
};


#endif //UNTITLED13_MAP_H
