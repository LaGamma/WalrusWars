#include <iostream>
#include "GameLogic.h"

GameLogic::GameLogic() {
    state = mainMenu;
    walrus1 = Player();
    walrus2 = Player();
    progression = 0;
}

void GameLogic::update(float dSec) {

    if (state == playing) {
        // process movement
        walrus1.tickMovement(dSec);
        walrus2.tickMovement(dSec);

        // apply deceleration
        walrus1.applyPassiveForce(dSec);
        walrus2.applyPassiveForce(dSec);


        // check collisions
        
        // if player has moved off the screen
            // trigger their death and respawn both players
        if (walrus1.getPos().x > 800.0f || walrus1.getPos().y > 600.0f || walrus1.getPos().x < 0 || walrus1.getPos().y < 0)
            handlePlayerDeath(1);
        if (walrus2.getPos().x > 800.0f || walrus2.getPos().y > 600.0f || walrus2.getPos().x < 0 || walrus2.getPos().y < 0)
            handlePlayerDeath(2);


    }


}

void GameLogic::generateMap() {
  stage.generateMap();
}

/*
 *1 param: walrus1 died
 * 2 param: walrus2 died
 * */
void GameLogic::handlePlayerDeath(int x) {

    //will have more need for separate cases later on to adjust the screen transition
	if (x == 1) {
	    std::cout<<"walrus1 died\n";
	    progression++;
	}
	else if (x == 2) {
	    std::cout<<"walrus2 died\n";
	    progression--;
	}
	if (progression >= 3) {
	    std::cout<<"walrus2 won!\n";
	    state = gameOverMenu;
	    //reset progression
	    progression = 0;
	}
	else if (progression <= -3) {
	    std::cout<<"walrus1 won!\n";
        state = gameOverMenu;
        progression = 0;
	}
	// respawn
    walrus1.spawn(sf::Vector2f(200.0f, 150.0f));
    walrus2.spawn(sf::Vector2f(600.0f, 450.0f));
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
    walrus1.spawn(sf::Vector2f(200.0f, 150.0f));
    walrus2.spawn(sf::Vector2f(600.0f, 450.0f));
}

GameLogic::GameState GameLogic::getState() {
    return state;
}

int GameLogic::getStageProgression() {
    return progression;
}
