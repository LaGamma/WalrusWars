#ifndef _PlayerController_H_
#define _PlayerController_H_

#include "Player.h"
#include "Controller.h"

class PlayerController : public Controller {

public:
    PlayerController();
    void update(float dSec);
private:
    Player player;

};


#endif
