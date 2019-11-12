#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "Controller.h"
#include "Animation.h"
#include "SoundManager.h"

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

    // major InputManager classes
    std::unique_ptr<Controller> player1Controller;
    std::unique_ptr<Controller> player2Controller;

    //animations and art
    SoundManager soundManager;
    Animation walrus1_animation;
    Animation walrus2_animation;
    Animation fish_animation1;
    Animation fish_animation2;
    Animation fish_animation3;
    sf::Texture spriteMapP1;
    sf::Texture spriteMapP2;
    sf::Texture spriteMapFish;
    sf::Texture menu_background;
    sf::Texture stage_progression;
    sf::Texture stage_progression_active;

    sf::RectangleShape ice;
    sf::RectangleShape player1;
    sf::RectangleShape player2;
    sf::CircleShape hitbox;
    sf::CircleShape collision_pt;
    sf::RectangleShape minimapbg;
    sf::CircleShape stage_veil;
    sf::CircleShape attackHitbox;


    //minimap individual stages
    sf::RectangleShape mmStage;
    sf::RectangleShape mmStageR;
    sf::RectangleShape mmStageR2;
    sf::RectangleShape mmStageL;
    sf::RectangleShape mmStageL2;

    sf::RectangleShape mmStagei;
    sf::RectangleShape mmStageRi;
    sf::RectangleShape mmStageR2i;
    sf::RectangleShape mmStageLi;
    sf::RectangleShape mmStageL2i;
};


#endif
