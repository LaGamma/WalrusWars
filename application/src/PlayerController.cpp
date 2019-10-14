#include "PlayerController.h"
#include <iostream>

PlayerController::PlayerController() {

};

void PlayerController::update(sf::RenderWindow &window, float dSec, int playerNum, GameLogic* logic) {

    if (playerNum == 1) {
        //process keyboard input for player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            std::cout << "1 Move Up\n";
            logic->walrus1->applyActiveForce(sf::Vector2f(0,-0.001));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            std::cout << "1 Move Down\n";
            logic->walrus1->applyActiveForce(sf::Vector2f(0,0.001));

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            std::cout << "1 Move Left\n";
            logic->walrus1->applyActiveForce(sf::Vector2f(-0.001,0));

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            std::cout << "1 Move Right\n";
            logic->walrus1->applyActiveForce(sf::Vector2f(0.001,0));

        }
        //std::cout << logic.walrus1.pos.x << "," << logic.walrus1.pos.y << "  " <<  logic.walrus1.vel.x << "," << logic.walrus1.vel.y << std::endl;
    } else {
        //process keyboard input for player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            std::cout << "2 Move Up\n";
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            std::cout << "2 Move Down\n";
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            std::cout << "2 Move Left\n";
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            std::cout << "2 Move Right\n";
        }
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
                //logic.pauseGame();
                break;
            case sf::Event::GainedFocus:
                //logic.resumeGame();
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::P) {
                    std::cout << "Pause\n";
                    //this->logic->togglePause();
                }
                break;
        }
    }
};
