#ifndef _BotController_H_
#define _BotController_H_
#include <queue>
#include "Controller.h"
#include <stack>


class BotController : public Controller {

  struct cell{
    int pi, pj, pos_x, pos_y;
    float f, g, h;
  };


  public:
      BotController();
      void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum);
  private:
      void calculatePath(GameLogic &logic, int playerNum);
      enum ControllerState {defensive, aggressive, transition};
      ControllerState state;
      std::queue<cell> openList;
      bool closedList[40][30];
      cell cellDetails[40][30];

      std::stack<int> directionStack;
      sf::Vector2f dir;
      sf::Vector2f accumulator;
};





#endif
