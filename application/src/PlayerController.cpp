#include "PlayerController.h"
#include <iostream>
#include <cmath>

//for ai, generally move towards center if player near edge shortest path towards where player is headed or is depending on difficulty
// , if in close proximity to fish or closer to fish than player shortest path to fish.

PlayerController::PlayerController() {

};

void PlayerController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim) {

    sf::Vector2f dir = sf::Vector2f(0,0);
    bool idle = false;
    bool resting = false;


    if (playerNum == 1) {
        //process keyboard input for player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dir.y -= 1;
            attackDir = dir;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dir.y += 1;
            attackDir = dir;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dir.x -= 1;
            attackDir = dir;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dir.x += 1;
            attackDir = dir;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            logic.walrus1.setMass(logic.walrus1.getMass()+0.001);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            logic.walrus1.setMass(logic.walrus1.getMass()-0.001);
        }
        logic.walrus1.applyActiveForce(dir, dSec);
        // idle state
        idle = (logic.walrus1.getStamina() > 99.99 && (sqrt((logic.walrus1.getVel().x * logic.walrus1.getVel().x) + (logic.walrus1.getVel().y * logic.walrus1.getVel().y)) < 0.001));
        //sleeping state
        resting = (logic.walrus1.getState() == Player::resting);

    } else {
        //process keyboard input for player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dir.y -= 1;
            attackDir = dir;
            //std::cout << "y:" << dir.y << "x:" << dir.x << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            dir.y += 1;
            attackDir = dir;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dir.x -= 1;
            attackDir = dir;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dir.x += 1;
            attackDir = dir;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
            logic.walrus2.setMass(logic.walrus2.getMass()+0.001);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
            logic.walrus2.setMass(logic.walrus2.getMass()-0.001);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && logic.walrus2.getStamina() >= 30) {
            attackAnimTimer = 0.30f;//make get switch time * 3, so its consistent if switch time changes
            anim.setCurrentSpritex(0); //set anim to first frame of attack animation
            attacking = true;
            //std::cout << "INITIATE ATTACK" << std::endl;
        }
        logic.walrus2.applyActiveForce(dir, dSec);
        // idle state
        idle = (logic.walrus2.getStamina() > 99.99 && (sqrt((logic.walrus2.getVel().x * logic.walrus2.getVel().x) + (logic.walrus2.getVel().y * logic.walrus2.getVel().y)) < 0.001));
        //sleeping state
        resting = (logic.walrus2.getState() == Player::resting);
    }

    //play animations
    if (attackAnimTimer > 0) {
        anim.updateAttack(dir, dSec);
        attackAnimTimer -= dSec;
        //std::cout << attackAnimTimer << std::endl;
    } else if (attackAnimTimer <= 0 && attacking){
        logic.handlePlayerAttack(playerNum, attackDir);
        attacking = false;
        //std::cout << "attacking" << attacking << std::endl;
        attackAnimTimer = 0;
    } else if (resting){
        anim.updateSleep(dSec);
    } else if (idle) {
        anim.setCurrentSprite(0, 0);
        attackDir = (sf::Vector2f(0, 1));
    } else if (attackAnimTimer <= 0 && !idle) {
        //updateMovement movement
        anim.updateMovement(dir, dSec);
        //std::cout << "MOVING" << std::endl;
    }




    // process events
    sf::Event Event;
    while (window.pollEvent(Event)) {
        switch (Event.type) {
            //window closed
            case sf::Event::Closed:
                window.close();
                break;
                //window out of focus
            case sf::Event::LostFocus:
                logic.togglePause();
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::P) {
                    std::cout << "Pause\n";
                    logic.togglePause();
                }
                break;
        }
    }
};