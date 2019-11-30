#include "BotController.h"
#include <iostream>
#include <cstring>
#include <cfloat>
#include <cmath>

//for ai, generally move towards center if player near edge shortest path towards where player is headed or is depending on difficulty
// , if in close proximity to fish or closer to fish than player shortest path to fish.

BotController::BotController() {
  state = defensive;
};

void BotController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) {

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

    calculateRays(logic, playerNum);

    dir = sf::Vector2f(0,0);

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


void BotController::calculateRays(GameLogic &logic, int playerNum){
  sf::Vector2f w_pos = (playerNum == 1) ? logic.walrus1.getPos() : logic.walrus2.getPos();
  sf::Vector2f w_vel = (playerNum == 1) ? logic.walrus1.getVel() : logic.walrus2.getVel();

  sf::Vector2f opponent_pos = (playerNum == 1) ? logic.walrus2.getPos() : logic.walrus1.getPos();


}

void BotController::calculateForce(GameLogic &logic, int playerNum) {

}
