#ifndef FISH_H
#define FISH_H

#include <SFML/System.hpp>

class Fish {

public:
    Fish(sf::Vector2f);

    void spawn(sf::Vector2f);
    sf::Vector2f getPosition();
    unsigned int getColor();

private:
    sf::Vector2f pos;
    int color; //0 is red, 1 is green, this will also act as powerup marker

};



#endif //FISH_H
