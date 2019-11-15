#ifndef _BotController_H_
#define _BotController_H_
#include <queue>
#include "Controller.h"


class BotController : public Controller {

  struct cell{
    int pi, pj, pos_x, pos_y;
    float f, g, h;
  };


  public:
      BotController();
      void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim);
      void changeState(int);
      int state;
      std::queue<cell> openList;
      bool closedList[40][30];
      cell cellDetails[40][30];
      void calculatePath(GameLogic &logic, int playerNum);
};





#endif
