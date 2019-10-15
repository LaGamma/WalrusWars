#include "CameraView.h"
#include <iostream>
#include <PlayerController.h>

CameraView::CameraView() {

}

void CameraView::init(GameLogic* gameLogic) {
    this->logic = gameLogic;
    this->player1Controller = createController(true);
    this->player2Controller = createController(true);
}

void CameraView::draw(sf::RenderWindow &window) {

    GameLogic::GameState state = this->logic->getState();
    switch (state) {
        case GameLogic::GameState::mainMenu:
            window.clear(sf::Color::Blue);
            break;
        case GameLogic::GameState::playing:
            window.clear(sf::Color::Green);
            this->drawPlayers(window);
            break;
        case GameLogic::GameState::pauseMenu:
            window.clear(sf::Color::Yellow);
            break;
        case GameLogic::GameState::gameOverMenu:
            window.clear(sf::Color::Red);
            break;
    }

    // display
    window.display();
}

void CameraView::drawPlayers(sf::RenderWindow &window) {

    sf::CircleShape circle;

    // draw ball
    circle.setPosition(this->logic->walrus2->getPos());
    circle.setRadius(this->logic->walrus1->getMass()*10);
    circle.setFillColor(sf::Color::Magenta);
    window.draw(circle);

    // draw ball
    circle.setPosition(this->logic->walrus1->getPos());
    circle.setRadius(this->logic->walrus1->getMass()*10);
    circle.setFillColor(sf::Color::Cyan);
    window.draw(circle);

}


void CameraView::switchScreen(int screen) {

}


void CameraView::processInput(sf::RenderWindow &window, float dSec) {


    if (this->logic->getState() == GameLogic::GameState::playing) {
        //ignore input here and instead handle input in instantiated player controllers
        this->player1Controller->update(window, dSec, 1, this->logic);
        this->player2Controller->update(window, dSec, 2, this->logic);

    } else {
        //handle game input here (for MainMenu, PauseMenu, GameOverMenu, etc)

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
                        this->logic->playGame();
                    } else if (Event.key.code == sf::Keyboard::P && this->logic->getState() == GameLogic::GameState::pauseMenu) {
                        std::cout << "toggle pause" << std::endl;
                        this->logic->togglePause();
                    }
                    break;
            }
        }

    }



}

std::unique_ptr<Controller> CameraView::createController(bool player) {
    if (player) {
        return std::unique_ptr<Controller>(new PlayerController());
    } else {
        //return std::unique_ptr<Controller>(new BotController());
    }
}
