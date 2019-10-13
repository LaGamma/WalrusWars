#include "PlayerController.h"
#include "CameraView.h"
#include <iostream>

PlayerController::PlayerController() {

};

void PlayerController::update(float dSec) {
    //process keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        std::cout << "Move Up\n";
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        std::cout << "Move Down\n";
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        std::cout << "Move Left\n";
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        std::cout << "Move Right\n";
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        std::cout << "Pause\n";
        //logic.pauseGame();
    }
};

