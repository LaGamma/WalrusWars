#include "Player.h"

Player::Player() {
  this->mass = 5;
  this->stamina = 100;
  this->pos = sf::Vector2f(1.0f, 1.0f);
  this->vel = sf::Vector2f(0.0f, 0.0f);
}

void Player::tickMovement(float dSec) {
    this->pos += (this->vel) * dSec;
}


void Player::applyPassiveForce(float dSec) {

    if (this->vel.x > 0) {
        this->vel.x -= 1.0f * dSec;
    } else if (this->vel.x < 0) {
        this->vel.x += 1.0f * dSec;
    }
    if (this->vel.y > 0) {
        this->vel.y -= 1.0f * dSec;
    } else if (this->vel.y < 0) {
        this->vel.y += 1.0f * dSec;
    }

}

void Player::applyActiveForce(sf::Vector2f force) {
    this->vel += force;
}

void Player::handlePowerUp(int powerup) {

}

// getters
sf::Vector2f Player::getPos() {
    return this->pos;
}
sf::Vector2f Player::getVel() {
    return this->vel;
}
float Player::getMass() {
    return this->mass;
}
