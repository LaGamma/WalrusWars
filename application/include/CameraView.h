#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include 'GameLogic.h'

class CameraView {
  public:
    CameraView();
    void init();
    void draw(sf::RenderWindow&); 
    void switchScreen(int);
  private:
    sf::Font font;
    GameLogic logic;
    //other drawable objects??

};


#endif
