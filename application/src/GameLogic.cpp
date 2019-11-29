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
    fish_accumulator = 0.0f;
    //sfx_volume = SFX_VOLUME_BASE;
    //music_volume = SFX_VOLUME_MAX
    sfx_volume = 50.0f;
    music_volume = 50.0f;
}

void GameLogic::update(float dSec) {

    if (state == playing) {

        // fish power-up generation
        // fish will be generated in water flopping (sometimes landing on ice)
        fish_accumulator += dSec;
        if (fish_list.size() < MAX_NUM_OF_FISH && fish_accumulator > 3.0) {
            fish_accumulator = 0;

            sf::Vector2f rand_spawn = sf::Vector2f(rand() % ((int)(7 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8), rand() % ((int)(5 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8));
            sf::Vector2f rand_target = sf::Vector2f(rand() % 160 - 80, rand() % 160 - 80);
            // make sure first jump is from water onto ice
            while ((stage.getTileDura((int)(rand_spawn.x / ICE_BLOCKS_SIZE_X), (int)(rand_spawn.y / ICE_BLOCKS_SIZE_Y), progression) > 0) ||
                    (stage.getTileDura((int)((rand_spawn.x + rand_target.x) / ICE_BLOCKS_SIZE_X), (int)((rand_spawn.y + rand_target.y) / ICE_BLOCKS_SIZE_Y), progression) <= 0)) {
                rand_spawn = sf::Vector2f(rand() % ((int)(7 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8), rand() % ((int)(5 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8));
                rand_target = sf::Vector2f(rand() % 160 - 80, rand() % 160 - 80);
            }

            fish_list.push_back(std::unique_ptr<Fish>(new Fish(rand_spawn, rand_target)));
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
        if(accumulator >= .6){
          stage.tickMelt(progression);
          accumulator -= .6;
        }

        // *check collisions* //
        sf::Vector2f w1_pos = walrus1.getPos();
        sf::Vector2f w2_pos = walrus2.getPos();
        float w1_mass = walrus1.getMass();
        float w2_mass = walrus2.getMass();

        // player1 - water collision
        if (stage.getTileDura((w1_pos.x)/ICE_BLOCKS_SIZE_X, (w1_pos.y)/ICE_BLOCKS_SIZE_Y, progression) <= 0) {
            if (!walrus1.isDead()) {
                handlePlayerDeath(1);
                splash = sfx_volume;
            }
        }
        // player2 - water collision
        if (stage.getTileDura((w2_pos.x)/ICE_BLOCKS_SIZE_X, (w2_pos.y)/ICE_BLOCKS_SIZE_Y, progression) <= 0) {
            if (!walrus2.isDead()) {
                handlePlayerDeath(2);
                splash = sfx_volume;
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
        if (dist < PLAYER_HITBOX_SCALE*(w1_mass + w2_mass) && !(walrus1.isDead() || walrus2.isDead())) {
            handlePlayerCollision();
        }

        // player1 attack - player 2 collision
        if (walrus1.getState() == Player::attacking) {
            //determine direction of attack
            p1AttackPoint = w1_pos + walrus1.getFacingDir() * (w1_mass / 3);

            posDiff = w2_pos - p1AttackPoint;
            dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
            if (!p1_attack_handling_in_progress && dist <= PLAYER_HITBOX_SCALE*(w2_mass + w1_mass)) {
                // use the unit vector between attack and player to direct knockback
                handlePlayerAttack(1, posDiff / dist);
            } else if (dist > PLAYER_HITBOX_SCALE*(w2_mass + w1_mass))  {
                p1_attack_handling_in_progress = false;
            }
        }
        else {
            p1_attack_handling_in_progress = false;
        }

        // player2 attack - player 1 collision
        if (walrus2.getState() == Player::attacking) {
            //determine direction of attack
            p2AttackPoint = w2_pos + walrus2.getFacingDir() * (w2_mass / 3);

            posDiff = w1_pos - p2AttackPoint;
            dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
            if (!p2_attack_handling_in_progress && dist <= PLAYER_HITBOX_SCALE*(w1_mass + w2_mass)) {
                std::cout<<"attack begun!"<<std::endl;
                // use the unit vector between attack and player to direct knockback
                handlePlayerAttack(2, posDiff / dist);
            } else if (dist > PLAYER_HITBOX_SCALE*(w1_mass + w2_mass)) {
                p2_attack_handling_in_progress = false;
            }
        }
        else {
            p2_attack_handling_in_progress = false;
        }

        // fish collisions
        std::list<std::unique_ptr<Fish>>::iterator fish;
        for (fish = fish_list.begin(); fish != fish_list.end(); fish++) {
            sf::Vector2f fish_pos = (*fish)->getPosition();
            // fish - player1 collision
            posDiff = w1_pos - fish_pos;
            dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
            if (dist < PLAYER_HITBOX_SCALE*w1_mass + FISH_SIZE && !walrus1.isDead()) {
                handleFishCollision(1, *fish);
                break;
            }
            // fish - player 2 collision
            posDiff = w2_pos - fish_pos;
            dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
            if (dist < PLAYER_HITBOX_SCALE*w2_mass + FISH_SIZE && !walrus2.isDead()) {
                handleFishCollision(2, *fish);
                break;
            }
            // fish - water collision
            if (stage.getTileDura(fish_pos.x/ICE_BLOCKS_SIZE_X, fish_pos.y/ICE_BLOCKS_SIZE_Y, progression) <= 0 && !(*fish)->flop_progress_timer) {
                handleFishCollision(0, *fish);
                break;
            }

            // tick update for living fish
            (*fish)->flop(dSec);
        }


    }


}

void GameLogic::handleBoundaryCollision(int walrus, float xpos) {

    if (walrus == 1 && xpos <= 0) {
        if (walrus2.isDead()) {
            progression--;
            std::cout<<"Round Number: " << round<< "\n";
            round += 1;
            fish_list.clear();
            walrus1.spawn(sf::Vector2f(15 * WINDOW_WIDTH / 16, WINDOW_HEIGHT / 2));
            walrus2.spawn(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
        } else {
            sf::Vector2f newVel = walrus1.getVel();
            newVel.x *= -1;
            walrus1.setVel(newVel);
            walrus1.tickUpdate(COLLISION_KNOCKBACK_TIME);
            border_bump = sfx_volume * BUMP_VOL_SCALE;
        }
    }

    else if (walrus == 2 && xpos >= WINDOW_WIDTH) {
        if (walrus1.isDead()) {
            progression++;
            std::cout<<"Round Number: " << round<< "\n";
            round += 1;
            fish_list.clear();
            walrus1.spawn(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
            walrus2.spawn(sf::Vector2f(WINDOW_WIDTH / 16, WINDOW_HEIGHT / 2));
        } else {
            sf::Vector2f newVel = walrus2.getVel();
            newVel.x *= -1;
            walrus2.setVel(newVel);
            walrus2.tickUpdate(COLLISION_KNOCKBACK_TIME);
            border_bump = sfx_volume * BUMP_VOL_SCALE;
        }
    }

    else if (walrus == 1 && xpos >= WINDOW_WIDTH) {
        sf::Vector2f newVel = walrus1.getVel();
        newVel.x *= -1;
        walrus1.setVel(newVel);
        walrus1.tickUpdate(COLLISION_KNOCKBACK_TIME);
        border_bump = sfx_volume * BUMP_VOL_SCALE;
    }

    else if (walrus == 2 && xpos <= 0) {
        sf::Vector2f newVel = walrus2.getVel();
        newVel.x *= -1;
        walrus2.setVel(newVel);
        walrus2.tickUpdate(COLLISION_KNOCKBACK_TIME);
        border_bump = sfx_volume * BUMP_VOL_SCALE;
    }


}

void GameLogic::handleFishCollision(int player, std::unique_ptr<Fish> &fish) {

    if (player == 1) {
        walrus1.handlePowerUp(fish->getColor());
        powerup = sfx_volume;
    } else if (player == 2) {
        walrus2.handlePowerUp(fish->getColor());
        powerup = sfx_volume;
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
  player_bump = magnitude * BUMP_VOL_SCALE * (sfx_volume / 100);
}

void GameLogic::handlePlayerAttack(int attacker, sf::Vector2f dir) {
    float attack_charge;
    if (attacker == 2) {
        p2_attack_handling_in_progress = true;
        attack_charge = walrus2.getAttackCharge();
        walrus1.setVel(walrus1.getVel() + dir * SLASH_ATTACK_POWER * attack_charge);
        walrus1.setStamina(walrus1.getStamina() - ATTACKED_STAMINA_LOST * attack_charge);
        player_hit = sfx_volume * attack_charge;
    } else if (attacker == 1) {
        p1_attack_handling_in_progress = true;
        attack_charge = walrus1.getAttackCharge();
        walrus2.setVel(walrus2.getVel() + dir * SLASH_ATTACK_POWER * attack_charge);
        walrus2.setStamina(walrus2.getStamina() - ATTACKED_STAMINA_LOST * attack_charge);
        player_hit = sfx_volume * attack_charge;
    }
}

void GameLogic::returnToMenu() {
    state = mainMenu;
    stage.generateMap();
    //reset progression
    progression = 0;
    //reset rounds
    round = 1;
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
	    if (walrus2.isDead()) {
	        resetGame();
	    } else {
            walrus1.kill();
            // check for game over
            if (progression == 2) {
                winner1 = false;
                state = gameOverMenu;
            }
	    }
	}


	else if (walrus == 2) {
        if (walrus1.isDead()) {
            resetGame();
        } else {
            walrus2.kill();
            // check for game over
            if (progression == -2) {
                winner1 = true;
                state = gameOverMenu;
            }
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
    walrus2.setColor(walrus1.getColor());
    walrus1.setColor(walrus2.getColor());
}

void GameLogic::handleOptionsMenu() {
    state = optionsMenu;
}

void GameLogic::handlePlayerSelectMenu() {
    state = playerSelectMenu;
}

void GameLogic::handleNameTextSubMenu() {
    state = nameTextSubMenu;
}
void GameLogic::handleColorSelectSubMenu() {
    state = colorSelectSubMenu;
}
GameLogic::GameState GameLogic::getState() {
    return state;
}

int GameLogic::getStageProgression() {
    return progression;
}
int GameLogic::getRound(){
    return round;
}
