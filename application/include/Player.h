#ifndef _Player_H_
#define _Player_H_

#include <SFML/System.hpp>


class Player {
  public:
    Player();
    void spawn(sf::Vector2f);

    // getters
    sf::Vector2f getPos();
    sf::Vector2f getVel();
    float getMass();

    void applyPassiveForce(float);
    void applyActiveForce(sf::Vector2f);
    void tickMovement(float);
    void handlePowerUp(int);

private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    float mass;
    float stamina;
};

#endif
