#ifndef FISH_H
#define FISH_H

#include <SFML/System.hpp>

class Fish {

public:
    Fish();

    void setPosition(sf::Vector2f);
    sf::Vector2f getPosition();
    unsigned int getColor();
    void setColor(unsigned int clr);

private:
    sf::Vector2f pos;
    unsigned int color; //0 is red, 1 is green, this will also act as powerup marker

};



#endif //FISH_H
