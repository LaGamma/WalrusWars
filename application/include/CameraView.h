#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "PlayerController.h"

class CameraView {
  public:
    CameraView();
    void init(GameLogic* logic);
    void processInput(sf::RenderWindow &window, float dSec);
    void draw(sf::RenderWindow &window);

    GameLogic* logic;

  private:
    sf::Font font;

    // major update classes
    std::unique_ptr<Controller> createController(bool player);
    std::unique_ptr<Controller> player1Controller;
    std::unique_ptr<Controller> player2Controller;

    // draw screen functions
    void drawGame(sf::RenderWindow &window);
    void drawMainMenu(sf::RenderWindow &window);
    void drawPauseMenu(sf::RenderWindow &window);
    void drawGameOverMenu(sf::RenderWindow &window);


};


#endif
