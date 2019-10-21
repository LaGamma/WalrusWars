#include "CameraView.h"
#include "Animation.h"
#include "PlayerController.h"
#include <iostream>

CameraView::CameraView() {

}

void CameraView::init() {
    player1Controller = createController(true);
    player2Controller = createController(true);
    //load in textures
    spriteMapP1.loadFromFile("../images/WWP1.png");
    spriteMapP2.loadFromFile("../images/WWP1.png");
    walrus1_animation.init(&spriteMapP1, sf::Vector2u(3,10), 0.15);
    walrus2_animation.init(&spriteMapP2, sf::Vector2u(3,10), 0.15);
    end_walrus1_animation.init(&spriteMapP1, sf::Vector2u(3,10), 0.15);
    end_walrus2_animation.init(&spriteMapP2, sf::Vector2u(3,10), 0.15);
    font.loadFromFile("../menuFont.ttf");
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
    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(800,600));
    rect.setFillColor(sf::Color(255,255,0,128));
    window.draw(rect);

}

void CameraView::drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic) {

    window.clear(sf::Color::Red);
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color(255,255,255,255));
    text.setPosition(window.getSize().x / 4.0, 50);


    if (logic.winner1)
    {
        //walrus1 won
        sf::CircleShape player1;

        player1.setRadius(logic.walrus1.getMass()*10);
        player1.setPosition(logic.walrus1.getPos().x - player1.getRadius(), logic.walrus1.getPos().y - player1.getRadius());
        //player1.setFillColor(sf::Color(180, 0, 255, 255));
        player1.setTexture(&spriteMapP1);
        player1.setTextureRect(end_walrus1_animation.uvRect);
        window.draw(player1);
        text.setString("Walrus 1 Won!");
    }

    else
    {
        //walrus2 won
        sf::CircleShape player2;

        player2.setRadius(logic.walrus2.getMass()*10);
        player2.setPosition(logic.walrus2.getPos().x - player2.getRadius(), logic.walrus2.getPos().y - player2.getRadius());
        player2.setFillColor(sf::Color(150, 150, 255, 255));
        player2.setTexture(&spriteMapP2);
        player2.setTextureRect(end_walrus2_animation.uvRect);
        window.draw(player2);
        text.setString("Walrus 2 Won!");
    }

    window.draw(text);
}

void CameraView::drawGame(sf::RenderWindow &window, GameLogic &logic) {

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

    sf::CircleShape player1;
    sf::CircleShape player2;
    sf::CircleShape hitbox;

    /*
    divide the image up in to its individual sprites by using dimensions of
    the image and dividing by the number of images in the rows and columns
    */
    sf::Vector2u textureSize = spriteMapP1.getSize();
    textureSize.x /= 3;
    textureSize.y /= 10;
    //circle.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 4, textureSize.x, textureSize.y));

    // draw Player1
    player1.setRadius(logic.walrus1.getMass()*10);
    player1.setPosition(logic.walrus1.getPos().x - player1.getRadius(), logic.walrus1.getPos().y - player1.getRadius());
    //player1.setFillColor(sf::Color(180, 0, 255, 255));
    player1.setTexture(&spriteMapP1);
    player1.setTextureRect(walrus1_animation.uvRect);

    // draw Player2
    player2.setRadius(logic.walrus2.getMass()*10);
    player2.setPosition(logic.walrus2.getPos().x - player2.getRadius(), logic.walrus2.getPos().y - player2.getRadius());
    player2.setFillColor(sf::Color(150, 150, 255, 255));
    player2.setTexture(&spriteMapP2);
    player2.setTextureRect(walrus2_animation.uvRect);

    //hitbox.setOutlineThickness(4);
    hitbox.setRadius(logic.walrus1.getMass()*6.5);
    hitbox.setPosition(logic.walrus1.getPos().x - hitbox.getRadius(), logic.walrus1.getPos().y - hitbox.getRadius());
    hitbox.setFillColor(sf::Color(0,0,0,0));
    window.draw(hitbox);
    hitbox.setRadius(logic.walrus2.getMass()*6.5);
    hitbox.setPosition(logic.walrus2.getPos().x - hitbox.getRadius(), logic.walrus2.getPos().y - hitbox.getRadius());
    window.draw(hitbox);

    // draw in order of depth
    if (logic.walrus1.getPos().y > logic.walrus2.getPos().y) {
        window.draw(player2);
        window.draw(player1);
    } else {
        window.draw(player1);
        window.draw(player2);
    }

    // draw collision point
    sf::CircleShape pt;
    pt.setPosition(logic.playerCollisionPoint - sf::Vector2f(5,5));
    pt.setRadius(5);
    pt.setFillColor(sf::Color::Red);
    window.draw(pt);

    //draw stage progression. For now display square progressing on bottom of screen
    sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(20,20));
    rectangle.setFillColor(sf::Color(255, 0, 0, 255));
    rectangle.setPosition(400.0f + (logic.getStageProgression() * (800.0f / 5.0f)), 600.0f - 25);
    window.draw(rectangle);


}


void CameraView::processInput(sf::RenderWindow &window, GameLogic &logic, float dSec) {


    if (logic.getState() == GameLogic::GameState::playing) {
        //ignore input here and instead handle input in instantiated player controllers
        player1Controller->update(window, logic, dSec, 1, walrus1_animation);
        player2Controller->update(window, logic, dSec, 2, walrus2_animation);

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
