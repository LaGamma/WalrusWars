#include "CameraView.h"
#include "Animation.h"
#include "PlayerController.h"
#include "BotController.h"
#include <iostream>

CameraView::CameraView() {

}

void CameraView::init() {
    //load in textures
    spriteMapP1.loadFromFile("../images/WalrusMovementSS.png");
    spriteMapP2.loadFromFile("../images/WalrusMovementSS.png");
    menu_background.loadFromFile("../images/menu_title.png");
    stage_progression.loadFromFile("../images/minimap3.png");
    walrus1_animation.init(&spriteMapP1, sf::Vector2u(3,10), 0.15);
    walrus2_animation.init(&spriteMapP2, sf::Vector2u(3,10), 0.15);
    end_walrus1_animation.init(&spriteMapP1, sf::Vector2u(3,10), 0.15);
    end_walrus2_animation.init(&spriteMapP2, sf::Vector2u(3,10), 0.15);
    font.loadFromFile("../fonts/menuFont.ttf");
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

    window.clear(sf::Color(150, 150, 150));
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(800,600));
    bg.setTexture(&menu_background);
    window.draw(bg);


    sf::Text Play("Play", font, 75);
    sf::Text Stats("Stats", font, 75);
    sf::Text Options("Options", font, 75);
    Play.setPosition(360, 325);
    Stats.setPosition(355, 400);
    Options.setPosition(330, 475);
    //handle coloring of selection
    if (main_menu_selection == 'P'){
        Stats.setFillColor(sf::Color::White);
        Play.setFillColor(sf::Color::Black);
    }
    if (main_menu_selection == 'S'){
        Play.setFillColor(sf::Color::White);
        Options.setFillColor(sf::Color::White);
        Stats.setFillColor(sf::Color::Black);
    }
    if (main_menu_selection == 'O'){
        Stats.setFillColor(sf::Color::White);
        Options.setFillColor(sf::Color::Black);
    }

    window.draw(Play);
    window.draw(Stats);
    window.draw(Options);
//settings could contain controls, difficulty, toggle music on off, toggle sound effects, ect.


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
    
    ice.setSize(sf::Vector2f(20,20));
    ice.setFillColor(sf::Color(50,247,250,200));
    ice.setOutlineColor(sf::Color(255,255,255));
    ice.setOutlineThickness(4);

    for(int i=0;i<40;i++){
      for(int j=0;j<30;j++){
        if(logic.stage.getTile(i,j,logic.getStageProgression())==1){
          ice.setPosition((i*20),(j*20));
          window.draw(ice);
        }
      }
    }

    /*
    divide the image up in to its individual sprites by using dimensions of
    the image and dividing by the number of images in the rows and columns
    */
    sf::Vector2u textureSize = spriteMapP1.getSize();
    textureSize.x /= 3;
    textureSize.y /= 10;
    //circle.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 4, textureSize.x, textureSize.y));

    // draw Player1
    player1.setSize(sf::Vector2f(logic.walrus1.getMass()*20, logic.walrus1.getMass()*20));
    player1.setPosition(logic.walrus1.getPos().x - player1.getSize().x/2, logic.walrus1.getPos().y - player1.getSize().y/2);
    //player1.setFillColor(sf::Color(180, 0, 255, 255));
    player1.setTexture(&spriteMapP1);
    player1.setTextureRect(walrus1_animation.uvRect);

    // draw Player2
    player2.setSize(sf::Vector2f(logic.walrus2.getMass()*20, logic.walrus2.getMass()*20));
    player2.setPosition(logic.walrus2.getPos().x - player2.getSize().x/2, logic.walrus2.getPos().y - player2.getSize().y/2);
    player2.setFillColor(sf::Color(150, 150, 255, 255));
    player2.setTexture(&spriteMapP2);
    player2.setTextureRect(walrus2_animation.uvRect);

    //hitbox.setOutlineThickness(4);
    hitbox.setRadius(logic.walrus1.getMass()*6);
    hitbox.setPosition(logic.walrus1.getPos().x - hitbox.getRadius(), logic.walrus1.getPos().y - hitbox.getRadius());
    hitbox.setFillColor(sf::Color(0,0,0,0));
    window.draw(hitbox);
    hitbox.setRadius(logic.walrus2.getMass()*6);
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
    collision_pt.setPosition(logic.playerCollisionPoint - sf::Vector2f(5,5));
    collision_pt.setRadius(5);
    collision_pt.setFillColor(sf::Color::Red);
    window.draw(collision_pt);

    //draw minimap background
    minimapbg.setSize(sf::Vector2f(440,70));
    minimapbg.setPosition(180,515);
    minimapbg.setFillColor(sf::Color::Blue);
    window.draw(minimapbg);

    //draw minimap
    minimap.setSize(sf::Vector2f(450,80));
    //minimap.setFillColor(sf::Color(50,247,250,100));
    minimap.setTexture(&stage_progression);
    minimap.setPosition(175, 500);
    window.draw(minimap);

    //draw stage indicator veil
    stage_veil.setRadius(55);
    stage_veil.setFillColor(sf::Color(0, 0, 255, 100));
    stage_veil.setPosition(348.0f + (logic.getStageProgression() * (470 / 5.0f)), 600.0f - 95);
    window.draw(stage_veil);

    /*
    //draw stage progression. For now display square progressing on bottom of screen
    sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(20,20));
    rectangle.setFillColor(sf::Color(255, 0, 0, 255));
    //rectangle.setOutlineColor(sf::Color(255,0,0));
    //rectangle.setOutlineThickness(3);
    rectangle.setPosition(400.0f + (logic.getStageProgression() * (800.0f / 5.0f)), 600.0f - 25);
    window.draw(rectangle);
    */


    //make the rectangle transparent rect that draws on top of the stage on the minimap. Space out stages on minimap better
}


void CameraView::processInput(sf::RenderWindow &window, GameLogic &logic, float dSec) {


    if (logic.getState() == GameLogic::GameState::playing) {
        // handle input in instantiated player controllers
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
                        //track which menu option the player is on
                        if (main_menu_selection == 'P' || main_menu_selection == 'S')
                            main_menu_selection = 'P';
                        else if (main_menu_selection == 'O')
                            main_menu_selection = 'S';
                    } else if (Event.key.code == sf::Keyboard::Down) {
                        std::cout << "menu down" << std::endl;
                        //track which menu option the player is on
                        if (main_menu_selection == 'O' || main_menu_selection == 'S')
                            main_menu_selection = 'O';
                        else if (main_menu_selection == 'P')
                            main_menu_selection = 'S';
                    } else if (Event.key.code == sf::Keyboard::Return) {
                        std::cout << "start game!" << std::endl;
                        createControllers(1);
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

void CameraView::createControllers(int players) {
    switch (players) {
        case 0:
            player1Controller = std::unique_ptr<Controller>(new BotController());
            player2Controller = std::unique_ptr<Controller>(new BotController());
            break;
        case 1:
            player1Controller = std::unique_ptr<Controller>(new PlayerController());
            player2Controller = std::unique_ptr<Controller>(new BotController());
            break;
        case 2:
            player1Controller = std::unique_ptr<Controller>(new PlayerController());
            player2Controller = std::unique_ptr<Controller>(new PlayerController());
            break;
    }
}
