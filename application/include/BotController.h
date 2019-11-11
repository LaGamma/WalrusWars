#ifndef _BotController_H_
#define _BotController_H_

#include "Controller.h"

class BotController : public Controller {

public:
    BotController();
    void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim);
    void changeState(int);
private:
    int state;
};


#endif
