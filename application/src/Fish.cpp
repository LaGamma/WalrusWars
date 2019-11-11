#include <iostream>
#include "Fish.h"

Fish::Fish() {

}

void Fish::setPosition(sf::Vector2f position) {
    pos = position;
}

sf::Vector2f Fish::getPosition() {
    return pos;
}

unsigned int Fish::getColor() {
    return color;
}
void Fish::setColor(unsigned int clr) {
    color = clr;
}