#ifndef _BotController2_H_
#define _BotController2_H_
#include <queue>
#include "Controller.h"
#include <stack>


class BotController2 : public Controller {

    struct cell {
        int pi, pj, pos_x, pos_y;
        float f, g, h;
    };


public:
    BotController2();
    void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum);
private:
    void calculatePath(GameLogic &logic, int playerNum);
    enum ControllerState {defensive, aggressive, transition};
    ControllerState state;
    std::queue<cell> openList;
    bool closedList[ICE_BLOCKS_WIDTH][ICE_BLOCKS_HEIGHT];
    cell cellDetails[ICE_BLOCKS_WIDTH][ICE_BLOCKS_HEIGHT];
    std::stack<int> directionStack;
    sf::Vector2f dir;
    sf::Vector2f accumulator;
};





#endif
