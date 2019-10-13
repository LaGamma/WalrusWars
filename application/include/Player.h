#ifndef _Player_H_
#define _Player_H_

#include <SFML/Graphics.hpp>

class Player {
  public:
    Player();
    void applyPassiveForce(sf::Vector2d);
    void applyActiveForce(sf::Vector2d);
    void handlePowerUp(int);
  private:
      sf::Vector2f pos;
      sf::Vector2f vel;
      float stamina;
      float mass;
};

#endif
