#include "CameraView.h"
#include "animation.h"
#include "PlayerController.h"
#include <iostream>

CameraView::CameraView() {

}

void CameraView::init() {
    player1Controller = createController(true);
    player2Controller = createController(true);
}

void CameraView::draw(sf::RenderWindow &window, GameLogic &logic, float dSec) {

    const GameLogic::GameState state = logic.getState();
    switch (state) {
        case GameLogic::GameState::mainMenu:
            drawMainMenu(window, logic);
            break;
        case GameLogic::GameState::pauseMenu:
            drawGame(window,logic, dSec);
            drawPauseMenu(window, logic);
            break;
        case GameLogic::GameState::playing:
            drawGame(window, logic, dSec);
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
    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(800,600));
    rect.setFillColor(sf::Color(255,255,0,128));
    window.draw(rect);

}

void CameraView::drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic) {

    window.clear(sf::Color::Red);

}

void CameraView::drawGame(sf::RenderWindow &window, GameLogic &logic, float dSec) {

    window.clear(sf::Color::Blue);
    sf::RectangleShape ice;
    ice.setSize(sf::Vector2f(20,20));
    ice.setFillColor(sf::Color(50,247,250,200));
    ice.setOutlineColor(sf::Color(255,255,255));
    ice.setOutlineThickness(4);

    for(int i=0;i<40;i++){
      for(int j=0;j<30;j++){
        if(logic.stage.getTile(i,j)==1){
          ice.setPosition((i*20-20),(j*20-20));
          window.draw(ice);
        }
      }
    }

    sf::CircleShape circle;
    //load in textures
    sf::Texture spriteMapP1;
    sf::Texture spriteMapP2;
    //sprite map must be in root dir
    spriteMapP1.loadFromFile("WWP1.png");
    spriteMapP2.loadFromFile("WWP1.png");

    Animation animation(&spriteMapP1, sf::Vector2u(3,10), 0.3);
    animation.update(animation.getSpriteRow(), dSec);
    /*
    divide the image up in to its individual sprites by using dimensions of
    the image and dividing by the number of images in the rows and columns
    */
    sf::Vector2u textureSize = spriteMapP1.getSize();
    textureSize.x /= 3;
    textureSize.y /= 10;
    //circle.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 4, textureSize.x, textureSize.y));
    circle.setTextureRect(animation.uvRect);

    // draw Player1
    circle.setRadius(logic.walrus1.getMass()*10);
    circle.setPosition(logic.walrus1.getPos().x - circle.getRadius(), logic.walrus1.getPos().y - circle.getRadius());
    //circle.setFillColor(sf::Color(180, 0, 255, 255));
    circle.setTexture(&spriteMapP1);
    window.draw(circle);
    // draw Player2
    circle.setRadius(logic.walrus2.getMass()*10);
    circle.setPosition(logic.walrus2.getPos().x - circle.getRadius(), logic.walrus2.getPos().y - circle.getRadius());
    circle.setFillColor(sf::Color(240, 0, 255, 255));
    window.draw(circle);

    // draw collision point
    circle.setPosition(logic.playerCollisionPoint - sf::Vector2f(5,5));
    circle.setRadius(5);
    circle.setFillColor(sf::Color::Red);
    window.draw(circle);

    //draw stage progression. For now display square progressing on bottom of screen
    sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(20,20));
    rectangle.setFillColor(sf::Color(255, 0, 0, 255));
    rectangle.setPosition(400.0f + (logic.getStageProgression() * (800.0f / 5.0f)), 600.0f - 25);
    window.draw(rectangle);


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
