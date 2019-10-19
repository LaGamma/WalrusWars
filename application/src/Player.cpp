#include <iostream>
#include "Player.h"

Player::Player() {

}

void Player::spawn(sf::Vector2f spawn_pos) {
    mass = 4.0f;
    stamina = 100.0f;
    pos = spawn_pos;
    vel = sf::Vector2f(0.0f, 0.0f);
}

void Player::tickMovement(float dSec) {
    pos += vel * dSec;
}


void Player::applyPassiveForce(float dSec) {

    float friction = 10.0f; // tunable (Should we make this a const variable for the player class?)

    if (vel.x > 0) {
        vel.x -= friction * dSec;
    } else if (vel.x < 0) {
        vel.x += friction * dSec;
    }
    if (vel.y > 0) {
        vel.y -= friction * dSec;
    } else if (vel.y < 0) {
        vel.y += friction * dSec;
    }

}

void Player::applyActiveForce(sf::Vector2f force_dir, float dSec) {

    float force_power = 1000.0f; // tunable (Should we make this a const variable for the player class?)

    if (stamina > 0) {
        stamina -= 0.001f;
        vel += force_dir * force_power * dSec;
    } else {
        //std::cout << "exhausted! can't move!" << std::endl;
        // set state to resting
    }
}
void Player::setVel(sf::Vector2f newVel) {
    vel = newVel;
}
void Player::setMass(float newMass) {
    mass = newMass;
}

void Player::handlePowerUp(int powerup) {

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
