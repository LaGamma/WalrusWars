#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "Controller.h"

class CameraView {
  public:
    CameraView();
    void init();
    void processInput(sf::RenderWindow &window, GameLogic &logic, float dSec);
    void draw(sf::RenderWindow &window, GameLogic &logic, float dSec);

  private:
    sf::Font font;

    // major update classes
    std::unique_ptr<Controller> createController(bool player);
    std::unique_ptr<Controller> player1Controller;
    std::unique_ptr<Controller> player2Controller;

    // draw screen functions
    void drawGame(sf::RenderWindow &window, GameLogic &logic, float dSec);
    void drawMainMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawPauseMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic);

};


#endif
