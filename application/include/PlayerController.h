#ifndef _PlayerController_H_
#define _PlayerController_H_

#include "Player.h"

class PlayerController {

public:
    PlayerController();
    void translateInput();
private:
    Player player;

};


#endif