#include "CameraView.h"
#include "PlayerController.h"
#include <iostream>

CameraView::CameraView() {

}

void CameraView::init() {
    player1Controller = createController(true);
    player2Controller = createController(true);
}

void CameraView::draw(sf::RenderWindow &window, GameLogic &logic) {

    const GameLogic::GameState state = logic.getState();
    switch (state) {
        case GameLogic::GameState::mainMenu:
            drawMainMenu(window, logic);
            break;
        case GameLogic::GameState::pauseMenu:
            drawGame(window,logic);
            drawPauseMenu(window, logic);
            break;
        case GameLogic::GameState::playing:
            drawGame(window, logic);
            break;
        case GameLogic::GameState::gameOverMenu:
            drawGameOverMenu(window, logic);
            break;
    }
    // display
    window.display();
}

void CameraView::drawMainMenu(sf::RenderWindow &window, GameLogic &logic) {

    window.clear(sf::Color::Blue);

}

void CameraView::drawPauseMenu(sf::RenderWindow &window, GameLogic &logic) {

    // draw transparent screen
    sf::RectangleShape rect;
    rect.setPosition(0,0);
    rect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    rect.setFillColor(sf::Color(255,255,0,128));
    window.draw(rect);

}

void CameraView::drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic) {

    window.clear(sf::Color::Red);

}

void CameraView::drawGame(sf::RenderWindow &window, GameLogic &logic) {

    window.clear(sf::Color::Green);

    sf::CircleShape circle;
    // draw Player1
    circle.setPosition(logic.walrus1.getPos());
    circle.setRadius(logic.walrus1.getMass()*10);
    circle.setFillColor(sf::Color(0, 255, 255, 255));
    window.draw(circle);
    // draw Player2
    circle.setPosition(logic.walrus2.getPos());
    circle.setRadius(logic.walrus1.getMass()*10);
    circle.setFillColor(sf::Color(255, 0, 255, 255));
    window.draw(circle);


}


void CameraView::processInput(sf::RenderWindow &window, GameLogic &logic, float dSec) {


    if (logic.getState() == GameLogic::GameState::playing) {
        //ignore input here and instead handle input in instantiated player controllers
        player1Controller->update(window, logic, dSec, 1);
        player2Controller->update(window, logic, dSec, 2);

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
                        logic.playGame();
                    } else if (Event.key.code == sf::Keyboard::P && logic.getState() == GameLogic::GameState::pauseMenu) {
                        std::cout << "toggle pause" << std::endl;
                        logic.togglePause();
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
