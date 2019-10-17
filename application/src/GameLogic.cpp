#include <iostream>
#include <cmath>
#include "GameLogic.h"

GameLogic::GameLogic() {
    state = mainMenu;
    walrus1 = Player();
    walrus2 = Player();
    progression = 0;
    stage = Stage();
    stage.generateMap();
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
        sf::Vector2f w1_pos = walrus1.getPos();
        sf::Vector2f w2_pos = walrus2.getPos();
        //if (w1_pos.x > 800.0f || w1_pos.y > 600.0f || w1_pos.x < 0 || w1_pos.y < 0)
        //    handlePlayerDeath(1);
        //if (w2_pos.x > 800.0f || w2_pos.y > 600.0f || w2_pos.x < 0 || w2_pos.y < 0)
        if (stage.getTile((w1_pos.x)/20, (w1_pos.y)/20) == 0)
            handlePlayerDeath(1);
        if (stage.getTile((w2_pos.x)/20, (w2_pos.y)/20) == 0)
            handlePlayerDeath(2);

        double dist = sqrt((w1_pos.x - w2_pos.x)*(w1_pos.x - w2_pos.x) + (w1_pos.y - w2_pos.y)*(w1_pos.y - w2_pos.y));

        if (dist < walrus1.getMass()*10 + walrus2.getMass()*10) {
            std::cout << "walruses are colliding!\n";
            //handle collision
        }


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
    walrus1.spawn(sf::Vector2f(400.0f, 200.0f));
    walrus2.spawn(sf::Vector2f(400.0f, 400.0f));
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
    walrus1.spawn(sf::Vector2f(400.0f, 200.0f));
    walrus2.spawn(sf::Vector2f(400.0f, 400.0f));
}

GameLogic::GameState GameLogic::getState() {
    return state;
}

int GameLogic::getStageProgression() {
    return progression;
}
