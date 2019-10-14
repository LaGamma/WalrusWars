#include <iostream>
#include "GameLogic.h"

GameLogic::GameLogic() {
    this->state = mainMenu;
    this->walrus1 = std::unique_ptr<Player>(new Player());
    this->walrus2 = std::unique_ptr<Player>(new Player());
}

void GameLogic::update(float dSec) {

    this->walrus1->tickMovement(dSec);
    std::cout << this->walrus1->pos.x << "," << this->walrus1->pos.y << "  " <<  this->walrus1->vel.x << "," << this->walrus1->vel.y << std::endl;
    //this->walrus2.pos += (this->walrus2.vel) * dSec;
    if (this->walrus1->vel.x > 0) {
        this->walrus1->vel.x -= 0.0001f * dSec;
    } else if (this->walrus1->vel.x < 0) {
        this->walrus1->vel.x += 0.0001f * dSec;
    }
    if (this->walrus1->vel.y > 0) {
        this->walrus1->vel.y -= 0.0001f * dSec;
    } else if (this->walrus1->vel.y < 0) {
        this->walrus1->vel.y += 0.0001f * dSec;
    }


}

void GameLogic::generateMap() {
  this->stage.generateMap();
}


void GameLogic::handlePlayerDeath(int x) {


}

void GameLogic::togglePause() {
  if (this->state == pauseMenu) {
      this->state = playing;
  } else if (this->state == playing) {
      this->state = pauseMenu;
  }
}

void GameLogic::playGame() {
    this->state = playing;
}

GameLogic::GameState GameLogic::getState() {
    return this->state;
}
