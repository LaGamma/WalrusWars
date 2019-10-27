#include <iostream>
#include "Player.h"

Player::Player() {

}

void Player::spawn(sf::Vector2f spawn_pos) {
    mass = 4.0f;
    stamina = 100.0f;
    pos = spawn_pos;
    vel = sf::Vector2f(0.0f, 0.0f);
    dead = false;
    resting = false;
}

void Player::tickMovement(float dSec) {
    pos += vel * dSec;
}


void Player::applyPassiveForce(float dSec) {

    if (vel.x > 0) {
        vel.x -= decelerate_strength * dSec;
    } else if (vel.x < 0) {
        vel.x += decelerate_strength * dSec;
    }
    if (vel.y > 0) {
        vel.y -= decelerate_strength * dSec;
    } else if (vel.y < 0) {
        vel.y += decelerate_strength * dSec;
    }



}

bool Player::isDead(){
  return dead;
}

void Player::kill(){
  dead = true;
}

void Player::applyActiveForce(sf::Vector2f force_dir, float dSec) {

    //don't move
    if (resting) {
        force_dir.x = 0.0;
        force_dir.y = 0.0;
    }

    if (stamina > 0) {
        //stamina -= 0.001f;
        //stamina -= 0.01f;
        vel += force_dir * accelerate_strength * dSec;
        //only make resting no longer false once 25% of stamina has been recovered
        if (resting && stamina >= 25.0f)
            resting = false;
    } else {
        //std::cout << "exhausted! can't move!" << std::endl;
        resting = true;
    }

    if (force_dir.x == 0.0f && force_dir.y == 0.0f) {
        applyStaminaChange(false);
    }
    else
        applyStaminaChange(true);
}
void Player::setVel(sf::Vector2f newVel) {
    vel = newVel;
}
void Player::setMass(float newMass) {
    mass = newMass;
}

void Player::handlePowerUp(int powerup) {

}

void Player::applyStaminaChange(bool moving) {
    //if moving, decrease stamina
    //if not moving, increase stamina
    //if resting is true, recover stamina faster
    //moving and resting should never both be true
    if (moving)
    {
        if (stamina > 0)
            stamina -= 0.1f;
    }
    else if (stamina < 100.0f && !resting)
        stamina += 0.01f;
    else
    {
        if (stamina <= 25.0f)
            stamina += 0.2f;
    }
}

//void resting() {
//
//}

// getters
sf::Vector2f Player::getPos() {
    return pos;
}
sf::Vector2f Player::getVel() {
    return vel;
}
float Player::getMass() {
    return mass;
}

float Player::getStamina() {
    return stamina;
}
