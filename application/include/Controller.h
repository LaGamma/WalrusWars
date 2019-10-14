#ifndef _Controller_H
#define _Controller_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"

class Controller {
  public:
    Controller();
    virtual void update(sf::RenderWindow &window, float dSec, int playerNum, GameLogic* logic) = 0;
};

#endif
