#include "PlayerController.h"
#include <iostream>

//for ai, generally move towards center if player near edge shortest path towards where player is headed or is depending on difficulty
// , if in close proximity to fish or closer to fish than player shortest path to fish.

PlayerController::PlayerController() {

};

void PlayerController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim) {

    sf::Vector2f dir = sf::Vector2f(0,0);


    if (playerNum == 1) {
        //process keyboard input for player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dir.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dir.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dir.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            logic.walrus1.setMass(logic.walrus1.getMass()+0.001);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            logic.walrus1.setMass(logic.walrus1.getMass()-0.001);
        }
        logic.walrus1.applyActiveForce(dir, dSec);
        // idle state
        if (logic.walrus1.getStamina() > 99.99 && logic.walrus1.getVel().x < 0.01 && logic.walrus1.getVel().y < 0.01) {
            dir = sf::Vector2f(0,1);
            logic.walrus1.setStamina(99.99);
        }

    } else {
        //process keyboard input for player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dir.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            dir.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dir.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
            logic.walrus2.setMass(logic.walrus2.getMass()+0.001);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
            logic.walrus2.setMass(logic.walrus2.getMass()-0.001);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && logic.walrus2.getStamina() >= 30) {
            attackAnimTimer = 0.30;//make get switch time * 3, so its consistent if switch time changes
            logic.handlePlayerAttack(1);
            std::cout << "INITIATE ATTACK" << std::endl;
        }
        logic.walrus2.applyActiveForce(dir, dSec);
        // idle state
        if (logic.walrus2.getStamina() > 99.99 && logic.walrus2.getVel().x < 0.01 && logic.walrus2.getVel().y < 0.01) {
            dir = sf::Vector2f(0,1);
            logic.walrus2.setStamina(99.99);
        }

    }

    //play animations
    if (attackAnimTimer > 0) {
        anim.updateAttack(dir, dSec);
        attackAnimTimer -= dSec;
        std::cout << attackAnimTimer << std::endl;
    }
    else{
        //reset attack animation variables
        attackAnimTimer = 0;
        //update movement
        anim.update(dir, dSec);
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