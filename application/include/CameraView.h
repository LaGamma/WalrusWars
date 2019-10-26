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
    void createControllers(int players);

    // draw screen functions
    void drawGame(sf::RenderWindow &window, GameLogic &logic);
    void drawMainMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawPauseMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic);
    
    sf::Font font;
    char main_menu_selection = 'P';

    // major update classes
    std::unique_ptr<Controller> player1Controller;
    std::unique_ptr<Controller> player2Controller;

    //animations and art
    Animation walrus1_animation;
    Animation walrus2_animation;
    Animation end_walrus1_animation;
    Animation end_walrus2_animation;
    sf::Texture spriteMapP1;
    sf::Texture spriteMapP2;
    sf::Texture menu_background;
    sf::Texture stage_progression;

    sf::RectangleShape ice;
    sf::RectangleShape player1;
    sf::RectangleShape player2;
    sf::CircleShape hitbox;
    sf::RectangleShape minimap;
    sf::CircleShape collision_pt;
    sf::RectangleShape minimapbg;
    sf::CircleShape stage_veil;

};


#endif
