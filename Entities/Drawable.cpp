//
// Created by Henrik Ravnborg on 2025-07-27.
//

#include "Drawable.h"

const sf::RectangleShape &Drawable::getShape() {
    return shape;
}

void Drawable::setShape(const sf::RectangleShape &shape) {
    this->shape = shape;
}

void Drawable::setShapePos(sf::Vector2f pos) {
   shape.setPosition(pos);
}

void Drawable::moveShape(sf::Vector2f vector) {
    shape.move(vector);
}

void Drawable::setColor(sf::Color color) {
    shape.setFillColor(color);
}

void Drawable::setSize(sf::Vector2f size) {
    shape.setSize(size);
}







