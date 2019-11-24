#include <iostream>
#include <cmath>
#include "Definitions.h"
#include "Player.h"

Player::Player() {

}

void Player::spawn(sf::Vector2f spawn_pos) {
    mass = INIT_MASS;
    stamina = MAX_STAMINA;
    pos = spawn_pos;
    vel = sf::Vector2f(0.0f, 0.0f);
    state = normal;
    speed_boost = 1.0f;
    facing_dir = sf::Vector2f(0,1);
    attack_charge = 0.0f;
    attack_release_timer = 0.0f;
    attack_duration_timer = 0.0f;
}

void Player::tickUpdate(float dSec) {
    // update movement
    pos += vel * dSec;

    // regenerate stamina
    switch (state) {
        case resting:
            stamina += RESTING_STAMINA_REGEN_RATE * dSec;
            if (stamina > STAMINA_THRESHOLD) {
                state = normal;
            }
            break;
        default:
            stamina += NORMAL_STAMINA_REGEN_RATE * dSec;
            break;
    }

    // cap stamina
    if (stamina > MAX_STAMINA) {
        stamina = MAX_STAMINA;

        // check if not moving and set to idle
        if (state == normal && sqrt((vel.x * vel.x) + (vel.y * vel.y)) < 0.1) {
            //facing_dir = sf::Vector2f(0,1);
            state = idle;
        }
    } else if (stamina < 0) {
        stamina = 0;
    }

    // if raising tusks, decrement attack release timer
    if (attack_release_timer > 0) {
        attack_release_timer -= dSec;
    } else if (state == raising_tusks && attack_release_timer <= 0) {
        attack_release_timer = 0;
        slash();
    }

    // if attacking, decrement attack duration timer
    if (attack_duration_timer > 0) {
        attack_duration_timer -= dSec;
    } else if (state == attacking && attack_duration_timer <= 0) {
        attack_duration_timer = 0;
        state = normal;
    }


}


void Player::applyPassiveForce(float dSec) {

    float resting_resistance = (state == resting) ? 2.0:1.0;

    if (vel.x > 0) {
        vel.x -= dSec * resting_resistance * DECELERATE_STRENGTH;
    } else if (vel.x < 0) {
        vel.x += dSec * resting_resistance * DECELERATE_STRENGTH;
    }
    if (vel.y > 0) {
        vel.y -= dSec * resting_resistance * DECELERATE_STRENGTH;
    } else if (vel.y < 0) {
        vel.y += dSec * resting_resistance * DECELERATE_STRENGTH;
    }


}

void Player::applyActiveForce(sf::Vector2f force_dir, float dSec) {

    if (force_dir.x != 0 || force_dir.y != 0) {
        facing_dir = force_dir;
    }

    switch (state) {
        case dead:
            force_dir *= DEAD_MOVEMENT_SCALEDOWN;
            break;
        case resting:
            force_dir *= RESTING_MOVEMENT_SCALEDOWN;
            break;
        case raising_tusks:
            // two possible strategies here (running cancels the attack OR scaledown movement - commented out)
            //if (force_dir.x != 0 || force_dir.y != 0) {
            //    state = running;
            //    attack_charge = 0;
            //}
            force_dir *= RAISING_TUSKS_MOVEMENT_SCALEDOWN;
            break;
        case attacking:
            force_dir *= ATTACKING_MOVEMENT_SCALEDOWN;
            break;
        case idle:
            facing_dir = sf::Vector2f(0,1);
            if (force_dir.x != 0 || force_dir.y != 0) {
                state = running;
            }
            break;
        default:
            if (force_dir.x == 0 && force_dir.y == 0) {
                state = normal;
            } else {
                state = running;
            }
    }

    stamina -= sqrt((force_dir.x * force_dir.x) + (force_dir.y * force_dir.y)) * dSec * MOVEMENT_STAMINA_COST_SCALE;
    force_dir *= speed_boost;
    vel += force_dir * dSec * ACCELERATE_STRENGTH;

    if (stamina < 0) {
        state = resting;
    }
}

void Player::setVel(sf::Vector2f newVel) {
    vel = newVel;
}
void Player::setStamina(float newStamina) {
    stamina = newStamina;
}

void Player::handlePowerUp(int powerup) {
    stamina += FISH_STAMINA_GAINED;
    if (powerup == 0) {
        speed_boost += FISH_SPEED_BOOST;
    }
    else if (powerup == 1) {
        mass += FISH_MASS_BOOST;
    }
}

void Player::raiseTusks(float dSec) {
    state = raising_tusks;
    attack_charge += dSec;
    // cap the charged attack
    if (attack_charge > MAX_ATTACK_CHARGE) {
        attack_charge = MAX_ATTACK_CHARGE;
    }
    attack_release_timer = ATTACK_RELEASE_TIMER;
}

void Player::slash() {
    std::cout<<"SLASH: "<<attack_charge<<std::endl;
    stamina -= ATTACK_STAMINA_COST;
    attack_duration_timer = ATTACK_DURATION_TIMER;
    attack_charge = 0.0f;
    state = attacking;
}

void Player::kill() {
    state = dead;
}
bool Player::isDead() {
    return (state == dead);
}
// getters
Player::PlayerState Player::getState() {
    return state;
}
sf::Vector2f Player::getPos() {
    return pos;
}
sf::Vector2f Player::getVel() {
    return vel;
}
sf::Vector2f Player::getFacingDir() {
    return facing_dir;
}
float Player::getMass() {
    return mass;
}
float Player::getStamina() {
    return stamina;
}
