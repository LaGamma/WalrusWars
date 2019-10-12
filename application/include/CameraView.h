#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"

class CameraView {
  public:
    CameraView();
    void init();
    void draw(sf::RenderWindow &window);
    void switchScreen(int);
    void processInput(sf::RenderWindow &window, float dSec);
  private:
    sf::Font font;
    GameLogic logic;
    // major update classes
    //Controller player1;
    //Controller player2;

    //other drawable objects??


};


#endif
