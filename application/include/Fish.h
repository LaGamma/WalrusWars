#ifndef FISH_H
#define FISH_H

#include <SFML/System.hpp>

class Fish {

public:
    Fish(sf::Vector2f, sf::Vector2f);

    void spawn(sf::Vector2f, sf::Vector2f);
    void flop(float);
    sf::Vector2f getPosition();
    unsigned int getColor();
    float flop_progress_timer;

private:
    sf::Vector2f pos;
    sf::Vector2f target_flop;
    float flop_trigger_timer;

    float flop_time_accumulator = 0.0f;
    int color; //0 is red, 1 is green, this will also act as powerup marker

};



#endif //FISH_H
