#include "PlayerController.h"
#include "CameraView.h"
#include <iostream>

PlayerController::PlayerController() {
  
};

void PlayerController::update(sf::RenderWindow &window, GameLogic &logic, float dSec) {
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
                if (Event.key.code == sf::Keyboard::Up) {
                    std::cout << "menu up" << std::endl;
                } else if (Event.key.code == sf::Keyboard::Down) {
                    std::cout << "menu down" << std::endl;
                } else if (Event.key.code == sf::Keyboard::Return) {
                    std::cout << "start game!" << std::endl;
                    logic.playGame();
                }
                break;
        }
    }
};
