#include <iostream>
#include <cmath>
#include "Player.h"

Player::Player() {

}

void Player::spawn(sf::Vector2f spawn_pos) {
    mass = 4.0f;
    stamina = 100.0f;
    pos = spawn_pos;
    vel = sf::Vector2f(0.0f, 0.0f);
    state = normal;
    speed = 1.0f;
}

// update movement and stamina recovery
void Player::tickUpdate(float dSec) {
    pos += vel * dSec;

    switch (state) {
        case resting:
            stamina += 20 * dSec;
            if (stamina > 25) {
                state = normal;
            }
            break;
        case normal:
            stamina += 10 * dSec;
            break;
    }

    // cap stamina
    if (stamina > 100.0) {
        stamina = 100.0;
    }

}


void Player::applyPassiveForce(float dSec) {

    float resting_resistance = (state == resting) ? 2.0:1.0;

    if (vel.x > 0) {
        vel.x -= decelerate_strength * dSec * resting_resistance;
    } else if (vel.x < 0) {
        vel.x += decelerate_strength * dSec * resting_resistance;
    }
    if (vel.y > 0) {
        vel.y -= decelerate_strength * dSec * resting_resistance;
    } else if (vel.y < 0) {
        vel.y += decelerate_strength * dSec * resting_resistance;
    }


}

void Player::applyActiveForce(sf::Vector2f force_dir, float dSec) {

    switch (state) {
        case dead:
            force_dir = force_dir * 0.0f;
            break;
        case resting:
            force_dir = force_dir * 0.2f;
            break;
        case raising_tusks:
            force_dir = force_dir * 0.5f;
            break;
        case attacking:
            force_dir = force_dir * 0.2f;
            break;
    }

    vel += force_dir * accelerate_strength * dSec;
    stamina -= sqrt((force_dir.x * force_dir.x) + (force_dir.y * force_dir.y)) *30*dSec;

    if (stamina < 0) {
        state = resting;
    }
    vel *= speed;
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
    if (powerup == 0) {
        speed += 0.01;
        std::cout<<"power up speed!";
    }
    else if (powerup == 1) {
        std::cout<<"power up mass!";
        mass += 1.0;
    }
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
float Player::getMass() {
    return mass;
}
float Player::getStamina() {
    return stamina;
}
