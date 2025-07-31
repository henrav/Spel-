//
// Created by Henrik Ravnborg on 2025-07-27.
//

#ifndef UNTITLED13_DRAWABLE_H
#define UNTITLED13_DRAWABLE_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

class Drawable {
protected:
    sf::RectangleShape shape;
public:
     const sf::RectangleShape &getShape() const;

     void setShape(const sf::RectangleShape &shape);

     void setShapePos(sf::Vector2f pos);

     void moveShape(sf::Vector2f vector);

     void setColor(sf::Color color);

     void setSize(sf::Vector2f size);

    Drawable() = default;

};


#endif //UNTITLED13_DRAWABLE_H
