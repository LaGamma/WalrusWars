#include "CameraView.h"
#include <iostream>
#include <PlayerController.h>

CameraView::CameraView() {

}

void CameraView::init() {


}

void CameraView::draw(sf::RenderWindow &window) {

    if (logic.getState() == GameLogic::GameState::playing) {
        window.clear(sf::Color::Green);
    }

    // display
    window.display();
}


void CameraView::switchScreen(int screen) {

}


void CameraView::processInput(sf::RenderWindow &window, float dSec) {


    if (logic.getState() == GameLogic::GameState::playing) {
        //ignore input here and instead handle input in instantiated player controllers
        this->player1Controller.update(dSec);
        this->player2Controller.update(dSec);

    } else {
        //handle game input here (for MainMenu, PauseMenu, GameOverMenu, etc)

        //process keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            std::cout << "Up\n";
            //logic.menuUp();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            std::cout << "Down\n";
            //logic.menuDown();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            std::cout << "R\n";
            //logic.resetGame();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            std::cout << "Q\n";
            //logic.quitGame(window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            //play game
            logic.playGame();
            this->player1Controller = PlayerController();
            this->player2Controller = PlayerController();
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
        }
    }

}
<<<<<<< Updated upstream








=======
>>>>>>> Stashed changes
