#ifndef _PlayerController_H_
#define _PlayerController_H_

#include "Controller.h"

class PlayerController : public Controller {

public:
    PlayerController();
    void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim);
    //handle attack sequence
    float attackAnimTimer = 0.0f; //time it takes to play attack animation through
    int attacking = 0; //avoid starting attack animation again while attack is in progress
};


#endif
