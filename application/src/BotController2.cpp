#include "BotController2.h"
#include <iostream>
#include <cstring>
#include <cfloat>
#include <cmath>

//for ai, generally move towards center if player near edge shortest path towards where player is headed or is depending on difficulty
// , if in close proximity to fish or closer to fish than player shortest path to fish.

BotController2::BotController2() {
    state = defensive;
    dir = sf::Vector2f(0,0);
    accumulator = sf::Vector2f(0,0);
};

void BotController2::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) {

    float bot_handicap = 2;  // higher number == slower bot

    bool opponent_dead = (playerNum == 1) ? logic.walrus2.isDead() : logic.walrus1.isDead();
    sf::Vector2f opponent_vel = (playerNum == 1) ? logic.walrus2.getVel() : logic.walrus1.getVel();
    sf::Vector2f self_vel = (playerNum == 1) ? logic.walrus1.getVel() : logic.walrus2.getVel();


    if(!opponent_dead && (state != defensive) && (opponent_vel.x>=30 || opponent_vel.y>=30)){
        state = defensive;
    }
    if(!opponent_dead && (state != aggressive) && (opponent_vel.x<30 || opponent_vel.y<30)){
        state = aggressive;
    }
    if(opponent_dead && (state != transition)){
        state = transition;
    }

    calculatePath(logic, playerNum);

    dir = sf::Vector2f(0,0);

    if(!directionStack.empty()) {
        if (directionStack.top() == 1) {
            dir.y += 1;
            dir.x += 1;
        } else if (directionStack.top() == 2) {
            dir.y += 1;
        } else if (directionStack.top() == 3) {
            dir.x -= 1;
            dir.y += 1;
        } else if (directionStack.top() == 4) {
            dir.x += 1;
        } else if (directionStack.top() == 5) {
            dir.x -= 1;
        } else if (directionStack.top() == 6) {
            dir.x += 1;
            dir.y -= 1;
        } else if (directionStack.top() == 7) {
            dir.y -= 1;
        } else if (directionStack.top() == 8) {
            dir.x -= 1;
            dir.y -= 1;
        }
    }

    if (playerNum == 1) {
        logic.walrus1.applyActiveForce(dir, dSec/bot_handicap);
    } else {
        logic.walrus2.applyActiveForce(dir, dSec/bot_handicap);
    }

    accumulator += self_vel * (dSec/bot_handicap);
    if (accumulator.x >= ICE_BLOCKS_SIZE_X || accumulator.y >= ICE_BLOCKS_SIZE_Y){
        if (!directionStack.empty()) {
            directionStack.pop();
        }
        accumulator = sf::Vector2f(0,0);
    }

    // process events
    sf::Event Event;
    while (window.pollEvent(Event)) {
        switch (Event.type) {
            //window closed
            case sf::Event::Closed:
                window.close();
                break;
                //window out of focus
            case sf::Event::LostFocus:
                logic.togglePause();
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::P) {
                    logic.togglePause();
                }
                break;
        }
    }
}


void BotController2::calculatePath(GameLogic &logic, int playerNum){
    sf::Vector2f w_pos = (playerNum == 1) ? logic.walrus1.getPos() : logic.walrus2.getPos();
    sf::Vector2f w_vel = (playerNum == 1) ? logic.walrus1.getVel() : logic.walrus2.getVel();

    sf::Vector2f opponent_pos = (playerNum == 1) ? logic.walrus2.getPos() : logic.walrus1.getPos();

    memset(closedList, false, sizeof (closedList));
    int i, j, x, y;
    int newCost;

    // set end/target position based on state
    if (state == defensive) {
        //calculate safe positions, for now middle of the stage.
        x = rand() % ICE_BLOCKS_WIDTH - 1;
        y = rand() % ICE_BLOCKS_HEIGHT - 1;
        while (logic.stage.getTileDura(x,y,logic.getStageProgression()) < 0.3) {
            x = rand() % ICE_BLOCKS_WIDTH - 1;
            y = rand() % ICE_BLOCKS_HEIGHT - 1;
        }
        //x = ICE_BLOCKS_WIDTH / 2;
        //y = ICE_BLOCKS_HEIGHT / 2;
    }
    else if (state == aggressive) {
        x = int(opponent_pos.x/ICE_BLOCKS_SIZE_X);
        y = int(opponent_pos.y/ICE_BLOCKS_SIZE_Y);
    }
    else if (state == transition) {
        x = (playerNum == 1) ? 0 : ICE_BLOCKS_WIDTH-1;
        y = ICE_BLOCKS_HEIGHT / 2;
    }

    // clear cellDetails
    for (i=0; i<ICE_BLOCKS_WIDTH; i++)
    {
        for (j=0; j<ICE_BLOCKS_HEIGHT; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].pos_x = i;
            cellDetails[i][j].pos_y = j;
            cellDetails[i][j].pi = -1;
            cellDetails[i][j].pj = -1;
        }
    }
    //crucial to start with an empty list!!
    while(!openList.empty()){
        openList.pop();
    }
    // add initial position to open list
    i = w_pos.x/ICE_BLOCKS_SIZE_X;
    j = w_pos.y/ICE_BLOCKS_SIZE_Y;
    cellDetails[i][j].f = 0;
    cellDetails[i][j].g = 0;
    cellDetails[i][j].h = 0;
    cellDetails[i][j].pi = i;
    cellDetails[i][j].pj = j;
    openList.push(cellDetails[i][j]);


    while(!openList.empty()){

        // init first node
        cell n = openList.front();
        i = n.pos_x;
        j = n.pos_y;
        openList.pop();
        closedList[i][j] = true;

        // if destination, end search
        if (i == x && j == y) {
            break;
        }

        // for each adjacent node n
        for (int neighbor_x = -1; neighbor_x <= 1; neighbor_x++) {
            for (int neighbor_y = -1; neighbor_y <= 1; neighbor_y++) {
                if ((neighbor_x == 0 && neighbor_y == 0)) {
                    continue;
                } //else if (openList[i+neighbor_x][j+neighbor_y])
                //closedList[i+neighbor_x][j+neighbor_y] ||

                newCost = cellDetails[i][j].g + std::abs((i+neighbor_x) - (w_pos.x/ICE_BLOCKS_SIZE_X)) + std::abs((j+neighbor_y) - (w_pos.y/ICE_BLOCKS_SIZE_Y));

                if(!closedList[i+neighbor_x][j+neighbor_y] && newCost < cellDetails[i+neighbor_x][j+neighbor_y].g && logic.stage.getTileDura(i+neighbor_x,j+neighbor_y,logic.getStageProgression())>=.5){
                    cellDetails[i+neighbor_x][j+neighbor_y].g = newCost;
                    cellDetails[i+neighbor_x][j+neighbor_y].h = std::abs((i+neighbor_x)-(x))+std::abs((j+neighbor_y)-(y));
                    cellDetails[i+neighbor_x][j+neighbor_y].f = cellDetails[i+neighbor_x][j+neighbor_y].h + cellDetails[i+neighbor_x][j+neighbor_y].g;
                    cellDetails[i+neighbor_x][j+neighbor_y].pi = i;
                    cellDetails[i+neighbor_x][j+neighbor_y].pj = j;
                    openList.push(cellDetails[i+neighbor_x][j+neighbor_y]);
                }
            }
        }


    }

    directionStack = std::stack<int>();
    i = w_pos.x/ICE_BLOCKS_SIZE_X;
    j = w_pos.y/ICE_BLOCKS_SIZE_Y;

    bool opponent_dead = (playerNum == 1) ? logic.walrus2.isDead() : logic.walrus1.isDead();
    if(!opponent_dead){

        while((i!=x)||(j!=y)){
            if((cellDetails[x][y].pi < x)&&(cellDetails[x][y].pj < y)) {  // top left corner (1)
                directionStack.push(1);
            }
            else if((cellDetails[x][y].pi == x)&&(cellDetails[x][y].pj < y)) {  // top center (2)
                directionStack.push(2);
            }
            else if((cellDetails[x][y].pi > x)&&(cellDetails[x][y].pj < y)) {  // top right corner (3)
                directionStack.push(3);
            }
            else if((cellDetails[x][y].pi < x)&&(cellDetails[x][y].pj == y)) {  // left (4)
                directionStack.push(4);
            }
            else if((cellDetails[x][y].pi > x)&&(cellDetails[x][y].pj == y)) {  // right (5)
                directionStack.push(5);
            }
            else if((cellDetails[x][y].pi < x)&&(cellDetails[x][y].pj > y)) {  // bottom left (6)
                directionStack.push(6);
            }
            else if((cellDetails[x][y].pi == x)&&(cellDetails[x][y].pj > y)) {  // bottom center (7)
                directionStack.push(7);
            }
            else if((cellDetails[x][y].pi > x)&&(cellDetails[x][y].pj > y)) {  // bottom center (8)
                directionStack.push(8);
            }
            x = cellDetails[x][y].pi;
            y = cellDetails[x][y].pj;
            if(x==-1||y==-1){
                break;
            }
        }
    }
}
