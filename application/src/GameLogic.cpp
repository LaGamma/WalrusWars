#include <iostream>
#include "GameLogic.h"

GameLogic::GameLogic() {
    state = mainMenu;
    walrus1 = Player();
    walrus2 = Player();
}

void GameLogic::update(float dSec) {

    if (state == playing) {
        // process movement
        walrus1.tickMovement(dSec);
        walrus2.tickMovement(dSec);

        // apply deceleration
        walrus1.applyPassiveForce(dSec);
        walrus2.applyPassiveForce(dSec);
    }


}

void GameLogic::generateMap() {
  stage.generateMap();
}


void GameLogic::handlePlayerDeath(int x) {

}

void GameLogic::togglePause() {
  if (state == pauseMenu) {
      state = playing;
  } else if (state == playing) {
      state = pauseMenu;
  }
}

void GameLogic::playGame() {
    state = playing;
    // hardcoded values should change to be relative to window dimension
    walrus1.spawn(sf::Vector2f(1.0,1.0));
    walrus2.spawn(sf::Vector2f(100.0,100.0));
}

GameLogic::GameState GameLogic::getState() {
    return state;
}
