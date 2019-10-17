#include <iostream>
#include "GameLogic.h"

GameLogic::GameLogic() {
    state = mainMenu;
    walrus1 = Player();
    walrus2 = Player();
    sf::Vector2u dim;
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
        if (walrus1.getPos().x > dim.x || walrus1.getPos().y > dim.y || walrus1.getPos().x < 0 || walrus1.getPos().y < 0)
            handlePlayerDeath(1);
        if (walrus2.getPos().x > dim.x || walrus2.getPos().y > dim.y || walrus2.getPos().x < 0 || walrus2.getPos().y < 0)
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
	    std::cout<<"walrus1 died";
	    progression++;
	}
	else if (x == 2) {
	    std::cout<<"walrus2 died";
	    progression--;
	}
	if (progression >= 3) {
	    std::cout<<"walrus1 won!";
	    state = gameOverMenu;
	    //reset progression
	    progression = 0;
	}
	else if (progression <= -3) {
	    std::cout<<"walrus2 won!";
        state = gameOverMenu;
        progression = 0;
	}
    sf::Vector2f spawn_vector;
    //below fixes conversion warnings between between Vector2u and Vector2f
    unsigned int spawn_x = dim.x; unsigned int spawn_y = dim.y;
    float x_float = (float) spawn_x / 2.0f; float y_float = (float) spawn_y / 2.0f;
    spawn_vector.x = x_float; spawn_vector.y = y_float;

    walrus1.spawn(spawn_vector);
    //set walrus2 a tenth of the screen size to the right and a tenth of the screen size down
    spawn_vector.x += dim.x / 10;
    spawn_vector.y -= dim.y / 10;
    walrus2.spawn(spawn_vector);
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

void GameLogic::dimensions(sf::Vector2u dim) {
    this->dim = dim;
}

GameLogic::GameState GameLogic::getState() {
    return state;
}

int GameLogic::getStageProgression() {
    return progression;
}
