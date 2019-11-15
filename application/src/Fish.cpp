#include <iostream>
#include "Fish.h"

Fish::Fish(sf::Vector2f pos) {
    spawn(pos);

}

void Fish::spawn(sf::Vector2f position) {
    pos = position;

    int rand_color = rand() % 10;
    if (rand_color < 5)
        color = 0;
    else
        color = 1;
}

sf::Vector2f Fish::getPosition() {
    return pos;
}

unsigned int Fish::getColor() {
    return color;
}