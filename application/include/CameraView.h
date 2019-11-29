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
    void drawOptionsMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawStatsMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawPlayerSelectMenu(sf::RenderWindow &window, GameLogic &logic);

    sf::Font font;
    char main_menu_selection = 'P';
    char options_menu_selection = 'S';
    char game_over_menu_selection = 'P';
    char player1_menu_selection = 'P';
    char color_selection = '1';
    bool colorSelector = false;
    bool enteringNameText = false;
    //char player2_menu_selection = 'P';
    int player1OrBot = -1; //-1 is bot, 1 is player
    int player2OrBot = -1; //-1 is bot, 1 is player

    // major InputManager classes
    std::unique_ptr<Controller> player1Controller;
    std::unique_ptr<Controller> player2Controller;

    //animations and art
    SoundManager soundManager;
    Animation walrus1_animation;
    Animation walrus2_animation;
    std::list<std::unique_ptr<Animation>> fish_animation_list;
    sf::Texture spriteMapWalrus;
    sf::Texture spriteMapFish;
    sf::Texture menu_background;
    sf::Texture stage_progression;
    sf::Texture stage_progression_active;
    sf::Texture playerPortrait;
    sf::Texture player1Select;
    sf::Texture player2Select;
    sf::Texture playerPortraitFrame;
    sf::Texture nameFrame;
    sf::Texture colorIcon;
    sf::Texture playerNeutralSelect;

    //player names
    std::string walrus1_name_str = "Wally";
    std::string walrus2_name_str = "Waldo";
    sf::Text walrus1_name;
    sf::Text walrus2_name;

    //player colors
    sf::Color player_color1 = sf::Color(255,255,255,255);
    sf::Color player_color2 = sf::Color(155,155,155,255);
    sf::Color player_color3 = sf::Color(255,155,155,255);
    sf::Color player_color4 = sf::Color(155,255,155,255);
    sf::Color player_color5 = sf::Color(155,155,255,255);

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

    float screenshake_magnitude;
    float screenshake_timer;
};


#endif
