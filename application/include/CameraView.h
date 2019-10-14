#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "PlayerController.h"

class CameraView {
  public:
    CameraView();
    void init(GameLogic* logic);
    void draw(sf::RenderWindow &window);
    void drawPlayers(sf::RenderWindow &window);
    void switchScreen(int);
    void processInput(sf::RenderWindow &window, float dSec);
    std::unique_ptr<Controller> createController(bool player);

    GameLogic* logic;
  private:
    sf::Font font;
    // major update classes
    std::unique_ptr<Controller> player1Controller;
    std::unique_ptr<Controller> player2Controller;

    //other drawable objects??


};


#endif
