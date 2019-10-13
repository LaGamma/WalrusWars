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
  this->state = pauseMenu;

}
void GameLogic::playGame() {
    this->state = playing;
}

GameLogic::GameState GameLogic::getState() {
    return this->state;
}
