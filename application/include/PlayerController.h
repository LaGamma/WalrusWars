#ifndef _PlayerController_H_
#define _PlayerController_H_

#include "Controller.h"

class PlayerController : public Controller {

public:
    PlayerController();
    void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) override;
};


#endif
