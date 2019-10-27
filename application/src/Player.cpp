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

    if (stamina > 0) {
        stamina -= dSec * (abs(force_dir.x) + abs(force_dir.y));
        vel += force_dir * accelerate_strength * dSec;
    } else {
        std::cout << "exhausted! can't move!" << std::endl;
        // set state to resting
    }

    if (force_dir.x == 0.0f && force_dir.y == 0.0f)
        applyStaminaChange(false, false);
    else
        applyStaminaChange(true, false);
}
void Player::setVel(sf::Vector2f newVel) {
    vel = newVel;
}
void Player::setMass(float newMass) {
    mass = newMass;
}
void Player::setStamina(float newStamina) {
    stamina = newStamina;
}

void Player::handlePowerUp(int powerup) {

}

void Player::applyStaminaChange(bool moving, bool resting) {
    //if moving, decrease stamina
    //if not moving, increase stamina
    //if resting is true, recover stamina faster
    //moving and resting should never both be true
    if (moving)
    {
        stamina -= 0.01f;
    }
    else if (resting && stamina < 100.0f)
    {
        stamina += 0.1f;
    }
    else if (stamina < 100.0f)
        stamina += 0.01f;
}

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
