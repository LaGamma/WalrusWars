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
            drawMainMenu(window);
            break;
        case GameLogic::GameState::pauseMenu:
            drawGame(window);
            drawPauseMenu(window);
            break;
        case GameLogic::GameState::playing:
            drawGame(window);
            break;
        case GameLogic::GameState::gameOverMenu:
            drawGameOverMenu(window);
            break;
    }
    // display
    window.display();
}

void CameraView::drawMainMenu(sf::RenderWindow &window) {

    window.clear(sf::Color::Blue);

}

void CameraView::drawPauseMenu(sf::RenderWindow &window) {

    // draw transparent screen
    sf::RectangleShape rect;
    rect.setPosition(0,0);
    rect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    rect.setFillColor(sf::Color(255,255,0,128));
    window.draw(rect);

}

void CameraView::drawGameOverMenu(sf::RenderWindow &window) {

    window.clear(sf::Color::Red);

}

void CameraView::drawGame(sf::RenderWindow &window) {

    window.clear(sf::Color::Green);

    sf::CircleShape circle;
    // draw Player1
    circle.setPosition(this->logic->walrus1->getPos());
    circle.setRadius(this->logic->walrus1->getMass()*10);
    circle.setFillColor(sf::Color(0, 255, 255, 255));
    window.draw(circle);
    // draw Player2
    circle.setPosition(this->logic->walrus2->getPos());
    circle.setRadius(this->logic->walrus1->getMass()*10);
    circle.setFillColor(sf::Color(255, 0, 255, 255));
    window.draw(circle);


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
