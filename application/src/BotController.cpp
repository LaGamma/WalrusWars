#include "BotController.h"
#include <iostream>
#include <cstring>
#include <cfloat>
#include <cmath>

//for ai, generally move towards center if player near edge shortest path towards where player is headed or is depending on difficulty
// , if in close proximity to fish or closer to fish than player shortest path to fish.

BotController::BotController() {
  state = defensive;
  dir = sf::Vector2f(0,0);
  accumulator = sf::Vector2f(0,0);
};

void BotController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) {

    float bot_handicap = 3;  // higher number == slower bot

    bool opponent_dead = (playerNum == 1) ? logic.walrus2.isDead() : logic.walrus1.isDead();
    sf::Vector2f opponent_vel = (playerNum == 1) ? logic.walrus2.getVel() : logic.walrus1.getVel();
    sf::Vector2f self_vel = (playerNum == 1) ? logic.walrus1.getVel() : logic.walrus2.getVel();

    if(!opponent_dead && (state != defensive) && (opponent_vel.x>=30 || opponent_vel.y>=30)){
        state = defensive;
        calculatePath(logic, playerNum);
    }
    if(!opponent_dead && (state != aggressive) && (opponent_vel.x<30 || opponent_vel.y<30)){
        state = aggressive;
        calculatePath(logic, playerNum);
    }
    if(opponent_dead && (state != transition)){
        state = transition;
        calculatePath(logic, playerNum);
    }

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
        directionStack.pop();
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


void BotController::calculatePath(GameLogic &logic, int playerNum){
  sf::Vector2f w_pos = (playerNum == 1) ? logic.walrus1.getPos() : logic.walrus2.getPos();
  sf::Vector2f w_vel = (playerNum == 1) ? logic.walrus1.getVel() : logic.walrus2.getVel();

  sf::Vector2f opponent_pos = (playerNum == 1) ? logic.walrus2.getPos() : logic.walrus1.getPos();

  memset(closedList, false, sizeof (closedList));
  int i, j;
  sf::Vector2i target;
  int newCost;

  std::cout<<state<<"\n";

  if(state == 0){
    //calculate safe positions, for now middle of the stage.
    target = sf::Vector2i(20, 15);
  }
  else if(state == 1){
    target = sf::Vector2i(int(opponent_pos.x/ICE_BLOCKS_SIZE_X), int(opponent_pos.y/ICE_BLOCKS_SIZE_Y));
  }
  else{
    target = (playerNum == 1) ? sf::Vector2i(0, 15) : sf::Vector2i(39, 15);
  }

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
  i = w_pos.x/ICE_BLOCKS_SIZE_X;
  j = w_pos.y/ICE_BLOCKS_SIZE_Y;
  while(!openList.empty()){
    openList.pop();
  } //crucial to start with an empty list!!

  cellDetails[i][j].f = 0;
  cellDetails[i][j].g = 0;
  cellDetails[i][j].h = 0;
  cellDetails[i][j].pi = i;
  cellDetails[i][j].pj = j;
  openList.push(cellDetails[i][j]);
  while(!openList.empty()){
    cell n = openList.front();
    i = n.pos_x;
    j = n.pos_y;
    openList.pop();
    closedList[i][j] = true;

    if (i == target.x && j == target.y){
      break;
    } //if destination, end search
    newCost = cellDetails[i][j].g+std::abs((i-1)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j-1)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i-1][j-1] && newCost<cellDetails[i-1][j-1].g && logic.stage.getTileDura(i-1,j-1,logic.getStageProgression())>=.5){
      cellDetails[i-1][j-1].g = newCost;
      cellDetails[i-1][j-1].h = std::abs((i-1)-(target.x))+std::abs((j-1)-(target.y));
      cellDetails[i-1][j-1].f = cellDetails[i-1][j-1].h + cellDetails[i-1][j-1].g;
      cellDetails[i-1][j-1].pi = i;
      cellDetails[i-1][j-1].pj = j;
      openList.push(cellDetails[i-1][j-1]);
    }
    newCost = cellDetails[i][j].g+std::abs((i)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j-1)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i][j-1] && newCost<cellDetails[i][j-1].g && logic.stage.getTileDura(i,j-1,logic.getStageProgression())>=.5){
      cellDetails[i][j-1].g = newCost;
      cellDetails[i][j-1].h = std::abs((i)-(target.x))+std::abs((j-1)-(target.y));
      cellDetails[i][j-1].f = cellDetails[i][j-1].h + cellDetails[i][j-1].g;
      cellDetails[i][j-1].pi = i;
      cellDetails[i][j-1].pj = j;
      openList.push(cellDetails[i][j-1]);
    }
    newCost = cellDetails[i][j].g+std::abs((i-1)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i-1][j] && newCost<cellDetails[i-1][j].g && logic.stage.getTileDura(i-1,j,logic.getStageProgression())>=.5){
      cellDetails[i-1][j].g = newCost;
      cellDetails[i-1][j].h = std::abs((i-1)-(target.x))+std::abs((j)-(target.y));
      cellDetails[i-1][j].f = cellDetails[i-1][j].h + cellDetails[i-1][j].g;
      cellDetails[i-1][j].pi = i;
      cellDetails[i-1][j].pj = j;
      openList.push(cellDetails[i-1][j]);
    }
    newCost = cellDetails[i][j].g+std::abs((i-1)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j+1)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i-1][j+1] && newCost<cellDetails[i-1][j+1].g && logic.stage.getTileDura(i-1,j+1,logic.getStageProgression())>=.5){
      cellDetails[i-1][j+1].g = newCost;
      cellDetails[i-1][j+1].h = std::abs((i-1)-(target.x))+std::abs((j+1)-(target.y));
      cellDetails[i-1][j+1].f = cellDetails[i-1][j+1].h + cellDetails[i-1][j+1].g;
      cellDetails[i-1][j+1].pi = i;
      cellDetails[i-1][j+1].pj = j;
      openList.push(cellDetails[i-1][j+1]);
    }
    newCost = cellDetails[i][j].g+std::abs((i)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j+1)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i][j+1] && newCost<cellDetails[i][j+1].g && logic.stage.getTileDura(i,j+1,logic.getStageProgression())>=.5){
      cellDetails[i][j+1].g = newCost;
      cellDetails[i][j+1].h = std::abs((i)-(target.x))+std::abs((j+1)-(target.y));
      cellDetails[i][j+1].f = cellDetails[i][j+1].h + cellDetails[i][j+1].g;
      cellDetails[i][j+1].pi = i;
      cellDetails[i][j+1].pj = j;
      openList.push(cellDetails[i][j+1]);
    }
    newCost = cellDetails[i][j].g+std::abs((i+1)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j+1)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i+1][j+1] && newCost<cellDetails[i+1][j+1].g && logic.stage.getTileDura(i+1,j+1,logic.getStageProgression())>=.5){
      cellDetails[i+1][j+1].g = newCost;
      cellDetails[i+1][j+1].h = std::abs((i+1)-(target.x))+std::abs((j+1)-(target.y));
      cellDetails[i+1][j+1].f = cellDetails[i+1][j+1].h + cellDetails[i+1][j+1].g;
      cellDetails[i+1][j+1].pi = i;
      cellDetails[i+1][j+1].pj = j;
      openList.push(cellDetails[i+1][j+1]);
    }
    newCost = cellDetails[i][j].g+std::abs((i+1)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j-1)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i+1][j-1] && newCost<cellDetails[i+1][j-1].g && logic.stage.getTileDura(i+1,j-1,logic.getStageProgression())>=.5){
      cellDetails[i+1][j-1].g = newCost;
      cellDetails[i+1][j-1].h = std::abs((i+1)-(target.x))+std::abs((j-1)-(target.y));
      cellDetails[i+1][j-1].f = cellDetails[i+1][j-1].h + cellDetails[i+1][j-1].g;
      cellDetails[i+1][j-1].pi = i;
      cellDetails[i+1][j-1].pj = j;
      openList.push(cellDetails[i+1][j-1]);
    }
    newCost = cellDetails[i][j].g+std::abs((i)-(w_pos.x/ICE_BLOCKS_SIZE_X))+std::abs((j+1)-(w_pos.y/ICE_BLOCKS_SIZE_Y));
    if(!closedList[i][j+1] && newCost<cellDetails[i][j+1].g && logic.stage.getTileDura(i,j+1,logic.getStageProgression())>=.5){
      cellDetails[i][j+1].g = newCost;
      cellDetails[i][j+1].h = std::abs((i)-(target.x))+std::abs((j+1)-(target.y));
      cellDetails[i][j+1].f = cellDetails[i][j+1].h + cellDetails[i][j+1].g;
      cellDetails[i][j+1].pi = i;
      cellDetails[i][j+1].pj = j;
      openList.push(cellDetails[i][j+1]);
    }


  }
  while(!directionStack.empty()){
    directionStack.pop();
  }
  i = w_pos.x/ICE_BLOCKS_SIZE_X;
  j = w_pos.y/ICE_BLOCKS_SIZE_Y;
  if(!logic.walrus2.isDead()){
    while((i!=x)||(j!=y)){
      //std::cout<<"i = "<<i<<"\n";
      //std::cout<<"j = "<<j<<"\n";
      //std::cout<<"x = "<<x<<"\n";
      //std::cout<<"y = "<<y<<"\n";
      if((cellDetails[x][y].pi<x)&&(cellDetails[x][y].pj<y)) {  // top left corner (1)
        directionStack.push(1);
      }
      else if((cellDetails[x][y].pi==x)&&(cellDetails[x][y].pj<y)) {  // top center (2)
        directionStack.push(2);
      }
      else if((cellDetails[x][y].pi>x)&&(cellDetails[x][y].pj<y)) {  // top right corner (3)
        directionStack.push(3);
      }
      else if((cellDetails[x][y].pi<x)&&(cellDetails[x][y].pj==y)) {  // left (4)
        directionStack.push(4);
      }
      else if((cellDetails[x][y].pi>x)&&(cellDetails[x][y].pj==y)) {  // right (5)
        directionStack.push(5);
      }
      else if((cellDetails[x][y].pi<x)&&(cellDetails[x][y].pj>y)) {  // bottom left (6)
        directionStack.push(6);
      }
      else if((cellDetails[x][y].pi==x)&&(cellDetails[x][y].pj>y)) {  // bottom center (7)
        directionStack.push(7);
      }
      else if((cellDetails[x][y].pi>x)&&(cellDetails[x][y].pj>y)) {  // bottom center (8)
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
