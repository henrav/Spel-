//
// Created by Henrik Ravnborg on 2025-09-07.
//

#ifndef UNTITLED13_DRAW_H
#define UNTITLED13_DRAW_H


#include <SFML/Graphics/RenderWindow.hpp>

class Draw {
public:

    template<typename T>
    static void draw(sf::RenderWindow& window, T drawable);

};



#endif //UNTITLED13_DRAW_H
