#include "BotController.h"
#include <iostream>

//for ai, generally move towards center if player near edge shortest path towards where player is headed or is depending on difficulty
// , if in close proximity to fish or closer to fish than player shortest path to fish.

BotController::BotController() {
  state = 0;
  //memset(closedList, false, sizeof (closedList));
  int i, j;
  for (i=0; i<40; i++)
  {
      for (j=0; j<30; j++)
      {
          //cellDetails[i][j].f = FLT_MAX;
          //cellDetails[i][j].g = FLT_MAX;
          //cellDetails[i][j].h = FLT_MAX;
          cellDetails[i][j].pi = -1;
          cellDetails[i][j].pj = -1;
      }
  }
};

void BotController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim) {


    float bot_handicap = 1.0;  // higher number == slower bot

    sf::Vector2f dir = sf::Vector2f(0,0);
    sf::Vector2f w1_pos = logic.walrus1.getPos();
    sf::Vector2f w2_pos = logic.walrus2.getPos();
    sf::Vector2f w1_vel = logic.walrus1.getVel();
    sf::Vector2f w2_vel = logic.walrus2.getVel();


    if (playerNum == 1) {
        //process input for player 1
        int i, j;
        if(w2_vel.x>=8 || w2_vel.y>=8){
          changeState(0);
        }else{
          changeState(1);
        }
        if(logic.walrus2.isDead()){
          changeState(2);
        }
        //if(state == 2){
        //  i = w1_pos.x/20;
        //  j = w1_pos.y/20;
        //  cellDetails[i][j].f = 0;
        //  cellDetails[i][j].g = 0;
        //  cellDetails[i][j].h = 0;
        //  cellDetails[i][j].pi = i;
        //  cellDetails[i][j].pj = j;
        //  openList.insert(cellDetails[i][j]);
        //  while(!openList.empty()){
        //    cell n = *openList.begin();
        //    openList.erase(openList.begin());
        //    closedList[i][j] = true;
        //    // here you start to go through all cells
        //  }
        //}
        if (w1_pos.y > w2_pos.y) {
            dir.y -= 1;
        } else if (w1_pos.y < w2_pos.y) {
            dir.y += 1;
        }
        if (w1_pos.x > w2_pos.x) {
            dir.x -= 1;
        } else if (w1_pos.x < w2_pos.x) {
            dir.x += 1;
        }

        //logic.walrus1.applyActiveForce(dir, dSec/bot_handicap);

    } else {
        //process input for player 2
        if(w1_vel.x>=8 || w1_vel.y>=8){
          changeState(0);
        }
        else{
          changeState(1);
        }
        if(logic.walrus1.isDead()){
          changeState(2);
        }
        if (w2_pos.y > w1_pos.y) {
            dir.y -= 1;
        } else if (w2_pos.y < w1_pos.y) {
            dir.y += 1;
        }
        if (w2_pos.x > w1_pos.x) {
            dir.x -= 1;
        } else if (w2_pos.x < w1_pos.x) {
            dir.x += 1;
        }
        //logic.walrus2.applyActiveForce(dir, dSec/bot_handicap);

    }
    anim.updateMovement(dir, dSec/bot_handicap);

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
};

void BotController::changeState(int state){
  if(state == 0){
    //std::cout<<"bot is fleeing\n";
    state = 0;
  }
  else if(state == 1){
    //std::cout<<"bot is attacking\n";
    state = 1;
  }
  else{
    //std::cout<<"bot wins\n";
    state = 2;
  }
}
