#ifndef _Player_H_
#define _Player_H_

#include <SFML/System.hpp>


class Player {
  public:
    Player();
    void applyPassiveForce(float);
    void applyActiveForce(sf::Vector2f);
    void tickMovement(float);
    void handlePowerUp(int);

    sf::Vector2f pos;
    sf::Vector2f vel;
    float mass;

private:
    float stamina;
};

#endif
