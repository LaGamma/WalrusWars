#include <iostream>
#include "GameLogic.h"

GameLogic::GameLogic() {
    this->state = mainMenu;
    this->walrus1 = std::unique_ptr<Player>(new Player());
    this->walrus2 = std::unique_ptr<Player>(new Player());
}

void GameLogic::update(float dSec) {

    // process movement
    this->walrus1->tickMovement(dSec);
    this->walrus2->tickMovement(dSec);

    // apply deceleration
    this->walrus1->applyPassiveForce(dSec);
    this->walrus2->applyPassiveForce(dSec);


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
