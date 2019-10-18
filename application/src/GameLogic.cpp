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
            handlePlayerCollision();
        }


    }


}

void GameLogic::handlePlayerCollision(){
  //find the velocity of collision along the line of collision
  sf::Vector2f newVel1;
  sf::Vector2f newVel2;
  sf::Vector2f velDiff;
  sf::Vector2f posDiff;
  velDiff = walrus1.getVel() - walrus2.getVel();
  posDiff = walrus1.getPos() - walrus2.getPos();
  float dotProduct = (velDiff.x*posDiff.x)+(velDiff.y*posDiff.y);
  newVel1 = walrus1.getVel() - (((2*walrus2.getMass())/(walrus1.getMass()+walrus2.getMass())) * (dotProduct/(float(sqrt((posDiff.x*posDiff.x)+(posDiff.y*posDiff.y)))))*posDiff);
  velDiff = walrus2.getVel() - walrus1.getVel();
  posDiff = walrus2.getPos() - walrus1.getPos();
  dotProduct = (velDiff.x*posDiff.x)+(velDiff.y*posDiff.y);
  newVel2 = walrus2.getVel() - (((2*walrus1.getMass())/(walrus1.getMass()+walrus2.getMass())) * (dotProduct/(float(sqrt((posDiff.x*posDiff.x)+(posDiff.y*posDiff.y)))))*posDiff);
  walrus1.setVel(newVel1);
  walrus2.setVel(newVel2);
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
