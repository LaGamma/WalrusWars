#ifndef _Controller_H_
#define _Controller_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "Animation.h"

class Controller {
  public:
    Controller();
    virtual void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim) = 0;
};

#endif
