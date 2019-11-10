#ifndef _BotController_H_
#define _BotController_H_
#include <set>
#include "Controller.h"


class BotController : public Controller {

  struct cell{
    int pi, pj;
    float f, g, h;
  };


  public:
      BotController();
      void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim);
      void changeState(int);
      int state;
      std::set<cell> openList;
      bool closedList[40][30];
      cell cellDetails[40][30];
};





#endif
