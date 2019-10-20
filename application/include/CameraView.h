#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "Controller.h"
#include "Animation.h"

class CameraView {
  public:
    CameraView();
    void init();
    void processInput(sf::RenderWindow &window, GameLogic &logic, float dSec);
    void draw(sf::RenderWindow &window, GameLogic &logic);

  private:
    sf::Font font;
    bool temp = true;

    // major update classes
    std::unique_ptr<Controller> createController(bool player);
    std::unique_ptr<Controller> player1Controller;
    std::unique_ptr<Controller> player2Controller;

    Animation walrus1_animation;
    Animation walrus2_animation;
    sf::Texture spriteMapP1;
    sf::Texture spriteMapP2;

    // draw screen functions
    void drawGame(sf::RenderWindow &window, GameLogic &logic);
    void drawMainMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawPauseMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic);

};


#endif
