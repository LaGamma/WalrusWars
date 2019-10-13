#include "GameLogic.h"

GameLogic::GameLogic() {
    this->state = mainMenu;
}

void GameLogic::update(float dSec) {


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
