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
    accumulator = 0;
}

void GameLogic::update(float dSec) {

    if (state == playing) {
       // if (progression >= 3 || progression <= -3)
         //   progression = 0;
        // process movement
        walrus1.tickMovement(dSec);
        walrus2.tickMovement(dSec);
        accumulator += dSec;
        if(accumulator >= 1) {
          stage.tickMelt(progression);
          accumulator -= 1;
        }

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
        if (stage.getTileDura((w1_pos.x)/20, (w1_pos.y)/20, progression) <= 0) {
            handlePlayerDeath(1);
		    } else if (stage.getTileDura((w2_pos.x)/20, (w2_pos.y)/20, progression) <= 0) {
            handlePlayerDeath(2);
        }
        sf::Vector2f posDiff = w1_pos - w2_pos;
        float dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));

        if (dist < 6.5*(walrus1.getMass() + walrus2.getMass())) {
            std::cout << "walruses are colliding!\n";
            handlePlayerCollision();
        }

    }


}

void GameLogic::handlePlayerCollision() {

  float knockback = 0.04; // tunable

  //find the velocity of collision along the line of collision
  sf::Vector2f w1_vel = walrus1.getVel();
  sf::Vector2f w2_vel = walrus2.getVel();
  sf::Vector2f w1_pos = walrus1.getPos();
  sf::Vector2f w2_pos = walrus2.getPos();
  float w1_mass = walrus1.getMass();
  float w2_mass = walrus2.getMass();

  // calculate point of collision for potentially adding a collision animation later
  playerCollisionPoint = sf::Vector2f(((w1_pos.x * w2_mass*20) + (w2_pos.x * w1_mass*20)) / (w1_mass*20 + w2_mass*20), ((w1_pos.y * w2_mass*20) + (w2_pos.y * w1_mass*20)) / (w1_mass*20 + w2_mass*20));

  // Elastic Collision handling algorithm implemented from:
  // http://cobweb.cs.uga.edu/~maria/classes/4070-Spring-2017/Adam%20Brookes%20Elastic%20collision%20Code.pdf

  // calculate the difference in positions and normalize into a unit vector
  sf::Vector2f posDiff = w1_pos - w2_pos;
  float length = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
  sf::Vector2f normal = sf::Vector2f(posDiff.x / length, posDiff.y / length);
  // calculate the tangent unit vector
  sf::Vector2f tangent = sf::Vector2f(normal.y*-1, normal.x);
  // dot product of normal and velocities
  float walrus1ScalarNorm = (normal.x*w1_vel.x)+(normal.y*w1_vel.y);
  float walrus2ScalarNorm = (normal.x*w2_vel.x)+(normal.y*w2_vel.y);
  // dot product of tangent and velocities
  float walrus1ScalarTan = (tangent.x*w1_vel.x)+(tangent.y*w1_vel.y);
  float walrus2ScalarTan = (tangent.x*w2_vel.x)+(tangent.y*w2_vel.y);
  // calculate elastic collision
  float walrus1NewScalarNorm = (walrus1ScalarNorm * (w1_mass - w2_mass) + 2 * w2_mass * walrus2ScalarNorm) / (w1_mass + w2_mass);
  float walrus2NewScalarNorm = (walrus2ScalarNorm * (w2_mass - w1_mass) + 2 * w1_mass * walrus1ScalarNorm) / (w1_mass + w2_mass);

  sf::Vector2f walrus1NewVecNorm = normal * walrus1NewScalarNorm;
  sf::Vector2f walrus2NewVecNorm = normal * walrus2NewScalarNorm;
  sf::Vector2f walrus1NewVecTan = tangent * walrus1ScalarTan;
  sf::Vector2f walrus2NewVecTan = tangent * walrus2ScalarTan;

  walrus1.setVel(walrus1NewVecTan + walrus1NewVecNorm);
  walrus2.setVel(walrus2NewVecTan + walrus2NewVecNorm);
  // avoid walrus sticking together occasionally
  walrus1.tickMovement(knockback);
  walrus2.tickMovement(knockback);
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
	    winner1 = false;
	    state = gameOverMenu;
	    //reset progression
	    progression = 0;
	}
	else if (progression <= -3) {
	    //add boolean for winner
        winner1 = true;
	    std::cout<<"walrus1 won!\n";
        state = gameOverMenu;
        progression = 0;
	}
	// respawn
    walrus1.spawn(sf::Vector2f(400.0f, 250.0f));
    walrus2.spawn(sf::Vector2f(400.0f, 350.0f));
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
