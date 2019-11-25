#include <iostream>
#include <cmath>
#include <Definitions.h>
#include "GameLogic.h"

GameLogic::GameLogic() {
    state = mainMenu;
    walrus1 = Player();
    walrus2 = Player();
    progression = 0;
    stage = Stage();
    stage.generateMap();
    accumulator = 0;
    bump = 0;
    splash = 0;
    fish_accumulator = 0.0f;
    //sfx_volume = SFX_VOLUME_BASE;
    //music_volume = SFX_VOLUME_MAX
    sfx_volume = 50.0f;
    music_volume = 50.0f;
}

void GameLogic::update(float dSec) {

    if (state == playing) {

        //fish powerup generation
        //need to fine tune these numbers, not sure where we want the fish to be generated
        //rand_create is just a simple way to randomize when fish are created
        fish_accumulator += dSec;
        if (fish_list.size() < 3 && fish_accumulator > 3.0) {
            fish_accumulator = 0;
            //sf::Vector2f stage_bounds = stage.getFishBounds(progression);
            //std::cout<<stage_bounds.y;
            int rand_x = rand() % (7 * (int) WINDOW_WIDTH / 8) + ((int) WINDOW_WIDTH / 8);
            int rand_y = rand() % (5 * (int) WINDOW_WIDTH / 8) + ((int) WINDOW_WIDTH / 8);
            //make sure not on water
            float tile_dur = stage.getTileDura(rand_x / ICE_BLOCKS_SIZE_X, rand_y / ICE_BLOCKS_SIZE_Y, progression);
            while (tile_dur <= 0) {
                rand_x = rand() % (7 * (int) WINDOW_WIDTH / 8) + ((int) WINDOW_WIDTH / 8);
                rand_y = rand() % (5 * (int) WINDOW_WIDTH / 8) + ((int) WINDOW_WIDTH / 8);
                tile_dur = stage.getTileDura(rand_x / ICE_BLOCKS_SIZE_X, rand_y / ICE_BLOCKS_SIZE_Y, progression);
            }
            fish_list.push_back(std::unique_ptr<Fish>(new Fish(sf::Vector2f(rand_x, rand_y))));
        }

        // process movement
        if (!walrus1.isDead()) {
            walrus1.tickUpdate(dSec);
            walrus1.applyPassiveForce(dSec);
        }
        if (!walrus2.isDead()) {
            walrus2.tickUpdate(dSec);
            walrus2.applyPassiveForce(dSec);
        }

        // melt stage
        accumulator += dSec;
        if(accumulator >= 1){
          stage.tickMelt(progression);
          accumulator -= 1;
        }

        // *check collisions* //
        sf::Vector2f w1_pos = walrus1.getPos();
        sf::Vector2f w2_pos = walrus2.getPos();

        // player1 - water collision
        if (stage.getTileDura((w1_pos.x)/ICE_BLOCKS_SIZE_X, (w1_pos.y)/ICE_BLOCKS_SIZE_Y, progression) <= 0) {
            if (!walrus1.isDead()) {
                handlePlayerDeath(1);
            }
        }
        // player2 - water collision
        if (stage.getTileDura((w2_pos.x)/ICE_BLOCKS_SIZE_X, (w2_pos.y)/ICE_BLOCKS_SIZE_Y, progression) <= 0) {
            if (!walrus2.isDead()) {
                handlePlayerDeath(2);
            }
        }

        // player - boundary collision
        if (w1_pos.x >= WINDOW_WIDTH || w1_pos.x <= 0) {
            handleBoundaryCollision(1, w1_pos.x);
        } else if (w2_pos.x >= WINDOW_WIDTH || w2_pos.x <= 0) {
            handleBoundaryCollision(2, w2_pos.x);
        }

        // player - player collision
        sf::Vector2f posDiff = w1_pos - w2_pos;
        float dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
        if (dist < PLAYER_HITBOX_SCALE*(walrus1.getMass() + walrus2.getMass()) && !(walrus1.isDead() || walrus2.isDead())) {
            handlePlayerCollision();
        }

        // fish collisions
        //have list of no more than 3 fish
        //check for collision of each fish
        std::list<std::unique_ptr<Fish>>::iterator fish;
        for (fish = fish_list.begin(); fish != fish_list.end(); fish++) {
            sf::Vector2f fish_pos = (*fish)->getPosition();
            // fish - player1 collision
            posDiff = w1_pos - fish_pos;
            dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
            if (dist < PLAYER_HITBOX_SCALE*walrus1.getMass() + FISH_SIZE && !walrus1.isDead()) {
                handleFishCollision(1, *fish);
                break;
            }
            // fish - player 2 collision
            posDiff = w2_pos - fish_pos;
            dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
            if (dist < PLAYER_HITBOX_SCALE*walrus2.getMass() + FISH_SIZE && !walrus2.isDead()) {
                handleFishCollision(2, *fish);
                break;
            }
            // fish - water collision
            if (stage.getTileDura(fish_pos.x/ICE_BLOCKS_SIZE_X, fish_pos.y/ICE_BLOCKS_SIZE_Y, progression) <= 0) {
                handleFishCollision(0, *fish);
                break;
            }
        }

    }


}

void GameLogic::handleBoundaryCollision(int walrus, float xpos) {

    if (walrus == 1 && xpos <= 0) {
        if (walrus2.isDead()) {
            progression--;
            walrus1.spawn(sf::Vector2f(15 * WINDOW_WIDTH / 16, WINDOW_HEIGHT / 2));
            walrus2.spawn(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
        } else {
            sf::Vector2f newVel = walrus1.getVel();
            newVel.x *= -1;
            walrus1.setVel(newVel);
            walrus1.tickUpdate(COLLISION_KNOCKBACK_TIME);
        }
    }

    else if (walrus == 2 && xpos >= WINDOW_WIDTH) {
        if (walrus1.isDead()) {
            progression++;
            walrus1.spawn(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
            walrus2.spawn(sf::Vector2f(WINDOW_WIDTH / 16, WINDOW_HEIGHT / 2));
        } else {
            sf::Vector2f newVel = walrus2.getVel();
            newVel.x *= -1;
            walrus2.setVel(newVel);
            walrus2.tickUpdate(COLLISION_KNOCKBACK_TIME);
        }
    }

    else if (walrus == 1 && xpos >= WINDOW_WIDTH) {
        sf::Vector2f newVel = walrus1.getVel();
        newVel.x *= -1;
        walrus1.setVel(newVel);
        walrus1.tickUpdate(COLLISION_KNOCKBACK_TIME);
    }

    else if (walrus == 2 && xpos <= 0) {
        sf::Vector2f newVel = walrus2.getVel();
        newVel.x *= -1;
        walrus2.setVel(newVel);
        walrus2.tickUpdate(COLLISION_KNOCKBACK_TIME);
    }

}

void GameLogic::handleFishCollision(int player, std::unique_ptr<Fish> &fish) {

    if (player == 1) {
        walrus1.handlePowerUp(fish->getColor());
    } else if (player == 2) {
        walrus2.handlePowerUp(fish->getColor());
    }

    fish_list.remove(fish);
}

void GameLogic::handlePlayerCollision() {

  //find the velocity of collision along the line of collision
  sf::Vector2f w1_vel = walrus1.getVel();
  sf::Vector2f w2_vel = walrus2.getVel();
  sf::Vector2f w1_pos = walrus1.getPos();
  sf::Vector2f w2_pos = walrus2.getPos();
  float w1_mass = walrus1.getMass();
  float w2_mass = walrus2.getMass();

  // calculate point of collision for potentially adding a collision animation later
  playerCollisionPoint = sf::Vector2f(((w1_pos.x * w2_mass) + (w2_pos.x * w1_mass)) / (w1_mass + w2_mass), ((w1_pos.y * w2_mass) + (w2_pos.y * w1_mass)) / (w1_mass + w2_mass));

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
  walrus1.tickUpdate(COLLISION_KNOCKBACK_TIME);
  walrus2.tickUpdate(COLLISION_KNOCKBACK_TIME);

  // power of collision
  sf::Vector2f velDiff = walrus1.getVel() - walrus2.getVel();
  float magnitude = sqrt((velDiff.x * velDiff.x) + (velDiff.y * velDiff.y));
  bump = magnitude * BUMP_VOL_SCALE;
}

void GameLogic::handlePlayerAttack(int playerNum, sf::Vector2f dir) {
    std::cout << "playerNum" << playerNum << std::endl;
    sf::Vector2f w1_pos = walrus1.getPos();
    sf::Vector2f w2_pos = walrus2.getPos();
    float w1_mass = walrus1.getMass();
    float w1_radius = w1_mass + 1; //+1 to avoid a regular collision
    float w2_mass = walrus2.getMass();
    float w2_radius = w2_mass + 1; //+1 to avoid a regular collision

    if (playerNum == 2){

        //determine direction of attack, direction conversion copied from animation
        attackCollisionPoint = w2_pos;
        int acpAdjustment = w2_radius / 2; //range for slash attack
        sf::Vector2f attackKnockBackDir;
        float slashAttackPower = SLASH_ATTACK_POWER;

        int hash = dir.x * 17 + dir.y * 7;
        std::cout << "hash:"<< hash << "\n" << std::endl;
        switch (hash) {
            case 17 + 7: //right down
                //adjust attack hitbox (hit coordinate) based on direction
                attackCollisionPoint.x += acpAdjustment;
                attackCollisionPoint.y += acpAdjustment;
                //variable used to determine knockback direction if hit
                attackKnockBackDir = (sf::Vector2f(slashAttackPower, slashAttackPower));
                break;
            case 17 - 7: //right up
                attackCollisionPoint.x += acpAdjustment;
                attackCollisionPoint.y -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(slashAttackPower, -slashAttackPower));
                break;
            case -17 + 7: //left down
                attackCollisionPoint.x -= acpAdjustment;
                attackCollisionPoint.y += acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(-slashAttackPower, slashAttackPower));
                break;
            case -17 - 7: //left up
                attackCollisionPoint.x -= acpAdjustment;
                attackCollisionPoint.y -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(-slashAttackPower, -slashAttackPower));
                break;
            case 17: //right
                attackCollisionPoint.x += acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(slashAttackPower, 0));
                break;
            case 7: //down
                attackCollisionPoint.y += acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(0, slashAttackPower));
                break;
            case -17: //left
                attackCollisionPoint.x -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(-slashAttackPower, 0));
                break;
            case -7: //up
                attackCollisionPoint.y -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(0, -slashAttackPower));
                break;
            case 0:
                break;
        }
        walrus2.setStamina(walrus2.getStamina() - ATTACK_STAMINA_COST);
        //if collision point inside other walrus hitbox, apply collision force
        std::cout << "x:" <<attackCollisionPoint.x <<"\n" << "y:" <<attackCollisionPoint.y <<"\n"<< std::endl;
        //follow circle formula to determine if point is inside other walrus hitbox
        if ((attackCollisionPoint.x - w1_pos.x) * (attackCollisionPoint.x - w1_pos.x) +
            (attackCollisionPoint.y - w1_pos.y) * (attackCollisionPoint.y - w1_pos.y) <= w1_radius * w1_radius) {
            //knock walrus
            std::cout << "SLASHED" <<"\n"<< std::endl;
            walrus1.setVel(walrus1.getVel() + attackKnockBackDir);
            walrus1.setStamina(walrus1.getStamina() - ATTACKED_STAMINA_LOST);
        }
        else{
            std::cout << "MISSED SLASH" <<"\n"<< std::endl;
         }
    }
    if (playerNum == 1) {

        //determine direction of attack, direction conversion copied from animation
        attackCollisionPoint = w1_pos;
        int acpAdjustment = w1_radius / 2; //range for slash attack
        sf::Vector2f attackKnockBackDir;
        float slashAttackPower = SLASH_ATTACK_POWER;

        int hash = dir.x * 17 + dir.y * 7;
        std::cout << "hash:" << hash << "\n" << std::endl;
        switch (hash) {
            case 17 + 7: //right down
                //adjust attack hitbox (hit coordinate) based on direction
                attackCollisionPoint.x += acpAdjustment;
                attackCollisionPoint.y += acpAdjustment;
                //variable used to determine knockback direction if hit
                attackKnockBackDir = (sf::Vector2f(slashAttackPower, slashAttackPower));
                break;
            case 17 - 7: //right up
                attackCollisionPoint.x += acpAdjustment;
                attackCollisionPoint.y -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(slashAttackPower, -slashAttackPower));
                break;
            case -17 + 7: //left down
                attackCollisionPoint.x -= acpAdjustment;
                attackCollisionPoint.y += acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(-slashAttackPower, slashAttackPower));
                break;
            case -17 - 7: //left up
                attackCollisionPoint.x -= acpAdjustment;
                attackCollisionPoint.y -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(-slashAttackPower, -slashAttackPower));
                break;
            case 17: //right
                attackCollisionPoint.x += acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(slashAttackPower, 0));
                break;
            case 7: //down
                attackCollisionPoint.y += acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(0, slashAttackPower));
                break;
            case -17: //left
                attackCollisionPoint.x -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(-slashAttackPower, 0));
                break;
            case -7: //up
                attackCollisionPoint.y -= acpAdjustment;
                attackKnockBackDir = (sf::Vector2f(0, -slashAttackPower));
                break;
            case 0:
                break;
        }
        walrus1.setStamina(walrus1.getStamina() - ATTACK_STAMINA_COST);
        //if collision point inside other walrus hitbox, apply collision force
        std::cout << "x:" << attackCollisionPoint.x << "\n" << "y:" << attackCollisionPoint.y << "\n" << std::endl;
        //follow circle formula to determine if point is inside other walrus hitbox
        if ((attackCollisionPoint.x - w2_pos.x) * (attackCollisionPoint.x - w2_pos.x) +
            (attackCollisionPoint.y - w2_pos.y) * (attackCollisionPoint.y - w2_pos.y) <= w2_radius * w2_radius) {
            //knock walrus
            std::cout << "SLASHED" << "\n" << std::endl;
            walrus2.setVel(walrus2.getVel() + attackKnockBackDir);
            walrus2.setStamina(walrus2.getStamina() - ATTACKED_STAMINA_LOST);
        } else {
            std::cout << "MISSED SLASH" << "\n" << std::endl;
        }
    }
}

void GameLogic::returnToMenu() {
  state = mainMenu;
  stage.generateMap();
}

void GameLogic::setSFXVolume(float vol) {
    float tmp = SFX_VOLUME_MAX;
    if (vol > tmp)
        vol = tmp;
    else if (vol <= 0.0)
        vol = 0;
    sfx_volume = vol;

}
void GameLogic::setMusicVolume(float vol) {
    float tmp = MUSIC_VOLUME_MAX;
    if (vol > tmp)
        vol = tmp;
    else if (vol <= 0.0)
        vol = 0;
    music_volume = vol;
}
float GameLogic::getSFXVolume() {
    return sfx_volume;
}
float GameLogic::getMusicVolume() {
    return music_volume;
}
/*
 *1 param: walrus1 died
 * 2 param: walrus2 died
 * */
void GameLogic::handlePlayerDeath(int walrus) {

    //check if both are dead (fixes respawn bug)
  if (walrus2.isDead() && walrus == 1) {
      resetGame();
  }

	if (walrus == 1) {
	  // check for game over
      if (progression == 2) {
          winner1 = false;
          state = gameOverMenu;
          //reset progression
          progression = 0;
          if(walrus2.isDead()){
            progression = 2;
          }
      }


      walrus1.kill();

	} else if (walrus == 2) {
	  //check for game over
      if (progression == -2) {
          winner1 = true;
          state = gameOverMenu;
          //reset progression
          progression = 0;
          if(walrus1.isDead()){
            progression = -2;
          }
      }

      walrus2.kill();
      if(walrus1.isDead()){
        resetGame();
      }

	}
    splash = 1;

}

void GameLogic::togglePause() {
  if (state == pauseMenu) {
      state = playing;
  } else if (state == playing) {
      state = pauseMenu;
  }
}

void GameLogic::resetGame() {
    state = playing;
    walrus1.spawn(sf::Vector2f(5 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2));
    walrus2.spawn(sf::Vector2f(3 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2));
}

void GameLogic::handleOptionsMenu() {
    state = optionsMenu;
}

GameLogic::GameState GameLogic::getState() {
    return state;
}

int GameLogic::getStageProgression() {
    return progression;
}
sf::Vector2f GameLogic::getAttackCollisionPoint() {
    return attackCollisionPoint;
}
