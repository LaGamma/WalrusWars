#ifndef FISH_H
#define FISH_H

#include <SFML/System.hpp>

class Fish {

public:
    Fish();

    void setPosition(sf::Vector2f);
    sf::Vector2f getPosition();

private:
    sf::Vector2f pos;
};



#endif //FISH_H
