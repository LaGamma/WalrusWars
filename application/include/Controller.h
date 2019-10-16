#ifndef _Controller_H_
#define _Controller_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"

class Controller {
  public:
    Controller();
    virtual void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) = 0;
};

#endif
