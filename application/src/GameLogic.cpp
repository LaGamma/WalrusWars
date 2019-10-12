#include "GameLogic.h"

GameLogic::GameLogic() {
    this->state = mainMenu;
}

void GameLogic::update(float) {

}

void GameLogic::generateMap() {

}

void GameLogic::handlePlayerDeath(int) {

}

void GameLogic::togglePause() {

}

GameLogic::GameState GameLogic::getState() {
    return this->state;
}

