#include "CameraView.h"
#include "Animation.h"
#include "PlayerController.h"
#include "BotController.h"
#include <iostream>
#include <Definitions.h>
#include <cmath>

CameraView::CameraView() {

}

void CameraView::init() {
    //load in textures
    spriteMapWalrus.loadFromFile("../images/WalrusSS.png");
    spriteMapFish.loadFromFile("../images/FishSS.png");
    menu_background.loadFromFile("../images/menu_title.png");
    stage_progression.loadFromFile("../images/MinimapPlatform.png");
    stage_progression_active.loadFromFile("../images/MinimapPlatformActive.png");
    font.loadFromFile("../fonts/menuFont.ttf");
    soundManager.load();
    walrus1_animation.init(&spriteMapWalrus, sf::Vector2u(3,11), 0.15);
    walrus2_animation.init(&spriteMapWalrus, sf::Vector2u(3,11), 0.15);

    for (int i = 0; i < MAX_NUM_OF_FISH; i++) {
        fish_animation_list.push_back(std::unique_ptr<Animation>(new Animation()));
        fish_animation_list.back()->init(&spriteMapFish, sf::Vector2u(2,2), 0.3);
    }

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
        case GameLogic::GameState::optionsMenu:
            drawOptionsMenu(window, logic);
            break;
    }
    // display
    window.display();
}

void CameraView::drawMainMenu(sf::RenderWindow &window, GameLogic &logic) {

    //main menu background
    window.clear(sf::Color(150, 150, 150));
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    bg.setTexture(&menu_background);
    window.draw(bg);

    //main menu items
    sf::Text Play("2 Player", font, 75);
    sf::Text Stats("1 Player", font, 75);
    sf::Text Options("Options", font, 75);
    Play.setPosition(33 * WINDOW_WIDTH / 80, 325 * WINDOW_HEIGHT / 600);
    Stats.setPosition(33 * WINDOW_WIDTH / 80, 2 * WINDOW_HEIGHT / 3);
    Options.setPosition(33 * WINDOW_WIDTH / 80, 475 * WINDOW_HEIGHT / 600);

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
    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    rect.setFillColor(sf::Color(255,255,0,128));
    window.draw(rect);

}

void CameraView::drawOptionsMenu(sf::RenderWindow &window, GameLogic &logic) {
    window.clear(sf::Color::Blue);

    sf::Text options_text;
    options_text.setFont(font);
    options_text.setCharacterSize(UI_TEXT_SIZE / 2);
    options_text.setFillColor(sf::Color(255, 255, 255, 255));
    options_text.setPosition(WINDOW_WIDTH / 2 - 25, 50);
    options_text.setString(OPTIONS_STRING);

    window.draw(options_text);

    sf::Text sfx_text;
    sfx_text.setFont(font);
    sfx_text.setCharacterSize(UI_TEXT_SIZE / 3);
    sfx_text.setFillColor(sf::Color(255, 255, 255, 255));
    sfx_text.setPosition(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 5);
    sfx_text.setString(SFX_VOLUME_STRING);

    float tmp = VOLUME_BAR_WIDTH;
    sf::RectangleShape sfx_line(sf::Vector2f(tmp, sfx_text.getGlobalBounds().height));
    //sf::RectangleShape sfx_line(sf::Vector2f(150, 20));
    sfx_line.setFillColor(sf::Color::Black);
    sfx_line.setPosition(sfx_text.getGlobalBounds().left + sfx_text.getGlobalBounds().width + 25,
                         sfx_text.getGlobalBounds().top);
    window.draw(sfx_line);

    sf::CircleShape sfx_choice(15);
    sfx_choice.setFillColor(sf::Color(0, 255, 255, 255));
    sfx_choice.setPosition(sfx_line.getPosition().x -sfx_choice.getRadius() + logic.getSFXVolume(), sfx_line.getPosition().y - 10);
    window.draw(sfx_choice);

    //music
    sf::Text music_text;
    music_text.setFont(font);
    music_text.setCharacterSize(UI_TEXT_SIZE / 3);
    music_text.setFillColor(sf::Color(255, 255, 255, 255));
    music_text.setPosition(WINDOW_WIDTH / 10, sfx_text.getPosition().y + 50);
    music_text.setString(MUSIC_VOLUME_STRING);

    tmp = MUSIC_VOLUME_MAX + 50;
    sf::RectangleShape music_line(sf::Vector2f(tmp, music_text.getGlobalBounds().height));
    music_line.setFillColor(sf::Color::Black);
    music_line.setPosition(sfx_line.getPosition().x, music_text.getGlobalBounds().top);
    window.draw(music_line);

    sf::CircleShape music_choice(15);
    music_choice.setFillColor(sf::Color(0, 255, 255, 255));
    music_choice.setPosition(music_line.getPosition().x + - music_choice.getRadius() + logic.getMusicVolume(), music_line.getPosition().y - 10);
    window.draw(music_choice);

    sf::Text quit_text;
    quit_text.setFont(font);
    quit_text.setCharacterSize(UI_TEXT_SIZE / 3);
    quit_text.setFillColor(sf::Color(255, 255, 255, 255));
    quit_text.setPosition(WINDOW_WIDTH / 10, music_text.getPosition().y + 50);
    quit_text.setString(QUIT_STRING);


    //handle coloring of selection
    if (options_menu_selection == 'S') {
        sfx_text.setFillColor(sf::Color::Black);
    }
    if (options_menu_selection == 'M') {
        music_text.setFillColor(sf::Color::Black);
    }
    if (options_menu_selection == 'Q') {
        quit_text.setFillColor(sf::Color::Black);
    }

    window.draw(sfx_text);
    window.draw(music_text);
    window.draw(quit_text);

}

void CameraView::drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic) {

    window.clear(sf::Color::Red);
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(UI_TEXT_SIZE);
    text.setFillColor(sf::Color(255,255,255,255));
    text.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 12);


    if (logic.winner1)
    {
        //walrus1 won
        walrus1_animation.setCurrentSprite(0,0);
        player1.setFillColor(logic.walrus1.getColor());
        player1.setTextureRect(walrus1_animation.uvRect);
        window.draw(player1);
        text.setString("Walrus 1 Won!");
    }

    else
    {
        //walrus2 won
        walrus2_animation.setCurrentSprite(0,0);
        player2.setFillColor(logic.walrus2.getColor());
        player2.setTextureRect(walrus2_animation.uvRect);
        window.draw(player2);
        text.setString("Walrus 2 Won!");
    }

    window.draw(text);
}

void CameraView::drawGame(sf::RenderWindow &window, GameLogic &logic) {

    window.clear(sf::Color::Blue);

    //draw ice blocks
    for (int i = 0; i < ICE_BLOCKS_WIDTH; i++) {
        for (int j = 0; j < ICE_BLOCKS_HEIGHT; j++) {
            float dura = logic.stage.getTileDura(i, j, logic.getStageProgression());
            if (dura > 0) {
                // draw ice graphics based on melt
                ice.setSize(sf::Vector2f(ICE_BLOCKS_SIZE_X * dura, ICE_BLOCKS_SIZE_Y * dura));
                ice.setPosition((i * ICE_BLOCKS_SIZE_X + ((ICE_BLOCKS_SIZE_X - ice.getSize().x) / 2)), (j * ICE_BLOCKS_SIZE_Y + ((ICE_BLOCKS_SIZE_Y - ice.getSize().y) / 2)));
                ice.setFillColor(sf::Color(50, 247, 250, 200 * dura));
                ice.setOutlineColor(sf::Color(255, 255, 255, 255));
                ice.setOutlineThickness(4 * dura);
                window.draw(ice);
            }
        }
    }

    // draw fish
    auto anim = fish_animation_list.begin();
    for (auto fish = logic.fish_list.begin(); fish != logic.fish_list.end(); fish++, anim++) {
        // size of drawn fish depends on fish flop - modeled with a simple quadratic to make it look like it's jumping towards screen
        double size_offset = FISH_SIZE + (-FISH_SIZE*((*fish)->flop_progress_timer-0.5)*((*fish)->flop_progress_timer-0.5) + 1);
        sf::CircleShape fish_circle = sf::CircleShape(size_offset);
        fish_circle.setPosition((*fish)->getPosition() - sf::Vector2f(size_offset, size_offset));
        fish_circle.setTexture(&spriteMapFish);
        fish_circle.setTextureRect((*anim)->uvRect);
        (*anim)->setCurrentSpriteY((*fish)->getColor());
        window.draw(fish_circle);
    }

    /*
    divide the image up in to its individual sprites by using dimensions of
    the image and dividing by the number of images in the rows and columns
    */
    sf::Vector2u textureSize = spriteMapWalrus.getSize();
    textureSize.x /= 3;
    textureSize.y /= 10;
    //circle.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 4, textureSize.x, textureSize.y));

    // draw Player1
    player1.setSize(sf::Vector2f(logic.walrus1.getMass(), logic.walrus1.getMass()));
    //player1.setPosition(logic.walrus1.getPos().x - player1.getSize().x / 2, logic.walrus1.getPos().y - player1.getSize().y / 2);
    player1.setPosition((logic.walrus1.getPos().x - player1.getSize().x / 2) + rand() % 2*logic.walrus1.getAttackCharge(), (logic.walrus1.getPos().y - player1.getSize().y / 2) + rand() % 2*logic.walrus1.getAttackCharge());
    player1.setFillColor(logic.walrus1.getColor());
    player1.setTexture(&spriteMapWalrus);
    player1.setTextureRect(walrus1_animation.uvRect);

    // draw Player2
    player2.setSize(sf::Vector2f(logic.walrus2.getMass(), logic.walrus2.getMass()));
    player2.setPosition(logic.walrus2.getPos().x - player2.getSize().x / 2,logic.walrus2.getPos().y - player2.getSize().y / 2);
    player2.setPosition((logic.walrus2.getPos().x - player2.getSize().x / 2) + rand() % 2*logic.walrus2.getAttackCharge(), (logic.walrus2.getPos().y - player2.getSize().y / 2) + rand() % 2*logic.walrus2.getAttackCharge());
    player2.setFillColor(logic.walrus2.getColor());
    player2.setTexture(&spriteMapWalrus);
    player2.setTextureRect(walrus2_animation.uvRect);

    // draw in order of depth
    if (logic.walrus1.getPos().y > logic.walrus2.getPos().y) {
        if (!logic.walrus2.isDead()) {
            window.draw(player2);
            player2.setFillColor(sf::Color(255*sin(15*logic.walrus2.getAttackCharge())+255, 0, 0, 40*logic.walrus2.getAttackCharge()));
            window.draw(player2);
        }
        if (!logic.walrus1.isDead()) {
            window.draw(player1);
            player1.setFillColor(sf::Color(255*sin(15*logic.walrus1.getAttackCharge())+255, 0, 0, 40*logic.walrus1.getAttackCharge()));
            window.draw(player1);
        }
    } else {
        if (!logic.walrus1.isDead()) {
            window.draw(player1);
            player1.setFillColor(sf::Color(255*sin(15*logic.walrus1.getAttackCharge())+255, 0, 0, 40*logic.walrus1.getAttackCharge()));
            window.draw(player1);
        }
        if (!logic.walrus2.isDead()) {
            window.draw(player2);
            player2.setFillColor(sf::Color(255*sin(15*logic.walrus2.getAttackCharge()+255), 0, 0, 40*logic.walrus2.getAttackCharge()));
            window.draw(player2);
        }
    }

    //hitbox.setOutlineThickness(4);
    hitbox.setRadius(logic.walrus1.getMass() * PLAYER_HITBOX_SCALE);
    hitbox.setPosition(logic.walrus1.getPos().x - hitbox.getRadius(), logic.walrus1.getPos().y - hitbox.getRadius());
    hitbox.setFillColor(sf::Color(0, 0, 0, 0));
    window.draw(hitbox);
    hitbox.setRadius(logic.walrus2.getMass() * PLAYER_HITBOX_SCALE);
    hitbox.setPosition(logic.walrus2.getPos().x - hitbox.getRadius(), logic.walrus2.getPos().y - hitbox.getRadius());
    window.draw(hitbox);


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(UI_TEXT_SIZE);
    text.setFillColor(sf::Color(255, 0, 0, 255));
    if (logic.walrus1.isDead()) {
        text.setPosition(3 * WINDOW_WIDTH / 4, (WINDOW_HEIGHT / 2) - (UI_TEXT_SIZE / 2));
        text.setString(GO_RIGHT);
        window.draw(text);
    } else if (logic.walrus2.isDead()) {
        text.setPosition(WINDOW_WIDTH / 4, (WINDOW_HEIGHT / 2) - (UI_TEXT_SIZE / 2));
        text.setString(GO_LEFT);
        window.draw(text);
    }
    // draw collision point
    collision_pt.setPosition(logic.playerCollisionPoint - sf::Vector2f(5, 5));
    collision_pt.setRadius(5);
    collision_pt.setFillColor(sf::Color::Red);
    window.draw(collision_pt);

    // draw w1 attack point
    if (logic.walrus1.getState() == Player::attacking) {
        collision_pt.setRadius(logic.walrus1.getMass()*PLAYER_HITBOX_SCALE);
        collision_pt.setPosition(logic.p1AttackPoint - sf::Vector2f(collision_pt.getRadius(), collision_pt.getRadius()));
        collision_pt.setFillColor(sf::Color(255,0,0,100));
        window.draw(collision_pt);
    }
    // draw w2 attack point
    if (logic.walrus2.getState() == Player::attacking) {
        collision_pt.setRadius(logic.walrus2.getMass()*PLAYER_HITBOX_SCALE);
        collision_pt.setPosition(logic.p2AttackPoint - sf::Vector2f(collision_pt.getRadius(), collision_pt.getRadius()));
        collision_pt.setFillColor(sf::Color(255,0,0,100));
        window.draw(collision_pt);
    }

    //draw minimap background
    /*
    minimapbg.setSize(sf::Vector2f(440, 70));
    minimapbg.setPosition(180, 515);
    minimapbg.setFillColor(sf::Color::Blue);
    window.draw(minimapbg);
    */

    //draw minimap, drawn as individual platforms
    mmStageL2.setSize(sf::Vector2f(140*WINDOW_WIDTH/800, WINDOW_HEIGHT/6));
    mmStageL.setSize(sf::Vector2f(170*WINDOW_WIDTH/800, 120*WINDOW_HEIGHT/600));
    mmStage.setSize(sf::Vector2f(200*WINDOW_WIDTH/800, 140*WINDOW_HEIGHT/600));
    mmStageR.setSize(sf::Vector2f(170*WINDOW_WIDTH/800, 120*WINDOW_HEIGHT/600));
    mmStageR2.setSize(sf::Vector2f(140*WINDOW_WIDTH/800, WINDOW_HEIGHT/6));
    mmStageL2.setTexture(&stage_progression);
    mmStageL.setTexture(&stage_progression);
    mmStage.setTexture(&stage_progression);
    mmStageR.setTexture(&stage_progression);
    mmStageR2.setTexture(&stage_progression);
    mmStageL2.setPosition(190*WINDOW_WIDTH/800, -25*WINDOW_HEIGHT/600);
    mmStageL.setPosition(240*WINDOW_WIDTH/800, -30*WINDOW_HEIGHT/600);
    mmStage.setPosition(300*WINDOW_WIDTH/800, -35*WINDOW_HEIGHT/600);
    mmStageR.setPosition(390*WINDOW_WIDTH/800, -30*WINDOW_HEIGHT/600);
    mmStageR2.setPosition(470*WINDOW_WIDTH/800, -25*WINDOW_HEIGHT/600);
    window.draw(mmStageL2);
    window.draw(mmStageL);
    window.draw(mmStage);
    window.draw(mmStageR);
    window.draw(mmStageR2);

    //initialize minimap indicators
    mmStageL2i.setSize(sf::Vector2f(140*WINDOW_WIDTH/800, 100*WINDOW_HEIGHT/600));
    mmStageLi.setSize(sf::Vector2f(170*WINDOW_WIDTH/800, 120*WINDOW_HEIGHT/600));
    mmStagei.setSize(sf::Vector2f(200*WINDOW_WIDTH/800, 140*WINDOW_HEIGHT/600));
    mmStageRi.setSize(sf::Vector2f(170*WINDOW_WIDTH/800, 120*WINDOW_HEIGHT/600));
    mmStageR2i.setSize(sf::Vector2f(140*WINDOW_WIDTH/800, 100*WINDOW_HEIGHT/600));
    mmStageL2i.setTexture(&stage_progression_active);
    mmStageLi.setTexture(&stage_progression_active);
    mmStagei.setTexture(&stage_progression_active);
    mmStageRi.setTexture(&stage_progression_active);
    mmStageR2i.setTexture(&stage_progression_active);
    mmStageL2i.setPosition(190*WINDOW_WIDTH/800, -25*WINDOW_HEIGHT/600);
    mmStageLi.setPosition(240*WINDOW_WIDTH/800, -30*WINDOW_HEIGHT/600);
    mmStagei.setPosition(300*WINDOW_WIDTH/800, -35*WINDOW_HEIGHT/600);
    mmStageRi.setPosition(390*WINDOW_WIDTH/800, -30*WINDOW_HEIGHT/600);
    mmStageR2i.setPosition(470*WINDOW_WIDTH/800, -25*WINDOW_HEIGHT/600);

    //draw indicator based on progression
    int progression = logic.getStageProgression();
    if (progression == -2)
        window.draw(mmStageL2i);
    else if (progression == -1)
        window.draw(mmStageLi);
    else if (progression == 0)
        window.draw(mmStagei);
    else if (progression == 1)
        window.draw(mmStageRi);
    else if (progression == 2)
        window.draw(mmStageR2i);

    //draw stage indicator veil
    /*
    stage_veil.setRadius(55);
    stage_veil.setFillColor(sf::Color(0, 0, 255, 100));
    stage_veil.setPosition(348.0f + (logic.getStageProgression() * (470 / 5.0f)), 600.0f - 95);
    window.draw(stage_veil);
    */

    if (logic.bump) {
        soundManager.playSound(SoundManager::SFX::bump, logic.bump);
        logic.bump = 0;
    }


    //make the rectangle transparent rect that draws on top of the stage on the minimap. Space out stages on minimap better

    //draw stamina boxes: these don't change
    sf::RectangleShape stamina_bar1 = sf::RectangleShape(sf::Vector2f(300*WINDOW_WIDTH/800, 25*WINDOW_HEIGHT/600));
    sf::RectangleShape stamina_bar2 = sf::RectangleShape(sf::Vector2f(300*WINDOW_WIDTH/800, 25*WINDOW_HEIGHT/600));
    stamina_bar1.setFillColor(sf::Color(255, 0, 0, 255));
    stamina_bar2.setFillColor(sf::Color(255, 0, 0, 255));
    stamina_bar1.setPosition(70*WINDOW_WIDTH/800, 60*WINDOW_HEIGHT/600);
    stamina_bar2.setPosition(stamina_bar1.getPosition().x + stamina_bar1.getSize().x + 70*WINDOW_WIDTH/800, 60*WINDOW_HEIGHT/600);
    window.draw(stamina_bar1);
    window.draw(stamina_bar2);

    //draw stamina gauges, these change
    //need to adjust dimensions to be based on walrus staminas
    //bar length is 300. Max stamina is 100
    sf::RectangleShape stamina_left1 = sf::RectangleShape(
            sf::Vector2f(stamina_bar1.getSize().x * logic.walrus1.getStamina()/100, stamina_bar1.getSize().y));
    sf::RectangleShape stamina_left2 = sf::RectangleShape(
            sf::Vector2f(stamina_bar1.getSize().x * logic.walrus2.getStamina()/100, stamina_bar2.getSize().y));
    stamina_left1.setFillColor(sf::Color(255, 255, 0, 255));
    stamina_left2.setFillColor(sf::Color(255, 255, 0, 255));
    stamina_left1.setPosition(stamina_bar1.getPosition());
    stamina_left2.setPosition(stamina_bar2.getPosition());
    window.draw(stamina_left1);
    window.draw(stamina_left2);

}



void CameraView::processInput(sf::RenderWindow &window, GameLogic &logic, float dSec) {

    if (logic.getState() == GameLogic::GameState::playing) {
        //update animations
        for (auto anim = fish_animation_list.begin(); anim != fish_animation_list.end(); anim++) {
            (*anim)->updateFish(dSec);
        }
        walrus1_animation.updateWalrus(logic.walrus1.getFacingDir(), logic.walrus1.getState(), dSec);
        walrus2_animation.updateWalrus(logic.walrus2.getFacingDir(), logic.walrus2.getState(), dSec);

        // handle input in instantiated player controllers
        player1Controller->update(window, logic, dSec, 1);
        player2Controller->update(window, logic, dSec, 2);

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

                case sf::Event::KeyPressed:

                    // which key was pressed?
                    switch(Event.key.code) {

                        case sf::Keyboard::Up:
                            //track which menu option the player is on
                            if (main_menu_selection == 'P' || main_menu_selection == 'S')
                                main_menu_selection = 'P';
                            else if (main_menu_selection == 'O')
                                main_menu_selection = 'S';
                            if (logic.getState() == GameLogic::GameState::optionsMenu) {
                                if (options_menu_selection == 'S' || options_menu_selection == 'M')
                                    options_menu_selection = 'S';
                                else if (options_menu_selection == 'Q')
                                    options_menu_selection = 'M';
                            }
                            break;

                        case sf::Keyboard::Down:
                            //track which menu option the player is on
                            if (main_menu_selection == 'O' || main_menu_selection == 'S')
                                main_menu_selection = 'O';
                            else if (main_menu_selection == 'P')
                                main_menu_selection = 'S';
                            if (logic.getState() == GameLogic::GameState::optionsMenu) {
                                if (options_menu_selection == 'S')
                                    options_menu_selection = 'M';
                                else if (options_menu_selection == 'M' || options_menu_selection == 'Q')
                                    options_menu_selection = 'Q';
                            }
                            break;

                        case sf::Keyboard::Right:
                            if (logic.getState() == GameLogic::GameState::optionsMenu) {
                                if (options_menu_selection == 'S') {
                                    logic.setSFXVolume(logic.getSFXVolume() + 10);
                                    std::cout<<logic.getSFXVolume();
                                }
                                else if (options_menu_selection == 'M') {
                                    logic.setMusicVolume(logic.getMusicVolume() + 10);
                                }
                            }
                            break;
                        case sf::Keyboard::Left:
                            if (logic.getState() == GameLogic::GameState::optionsMenu) {
                                if (options_menu_selection == 'S') {
                                    logic.setSFXVolume(logic.getSFXVolume() - 10);
                                }
                                else if (options_menu_selection == 'M') {
                                    logic.setMusicVolume(logic.getMusicVolume() - 10);
                                }
                            }
                            break;
                        case sf::Keyboard::Return:

                            switch (logic.getState()) {
                                case GameLogic::GameState::mainMenu:
                                    if (main_menu_selection == 'P') {
                                        std::cout << "2 player game!" << std::endl;
                                        createControllers(2);
                                        logic.resetGame();
                                    } else if (main_menu_selection == 'S') {
                                        std::cout << "1 player game!" << std::endl;
                                        createControllers(1);
                                        logic.resetGame();
                                    } else if (main_menu_selection == 'O') {
                                        std::cout << "options menu" << std::endl;
                                        logic.handleOptionsMenu();
                                    }
                                    break;
                                case GameLogic::GameState::pauseMenu:
                                    logic.togglePause();
                                    break;
                                case GameLogic::GameState::gameOverMenu:
                                    logic.returnToMenu();
                                    break;
                                case GameLogic::GameState::optionsMenu:
                                    if(options_menu_selection == 'Q') {
                                        options_menu_selection = 'S';
                                        logic.returnToMenu();
                                    }
                                    break;
                            }
                            break;

                        case sf::Keyboard::P:
                            logic.togglePause();
                            break;
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
