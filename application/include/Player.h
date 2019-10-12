#ifndef _Player_H_
#define _Player_H_

#include <SFML/System.hpp>

class Player {

public:
    Player();
    void applyPassiveForce();
    void applyActiveForce(sf::Vector2f);
    void handlePowerup(int);
private:
    float stamina;
    float mass;
    sf::Vector2f position;
    sf::Vector2f velocity;

};


#endif

