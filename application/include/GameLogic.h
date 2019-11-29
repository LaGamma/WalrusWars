#ifndef _GameLogic_H_
#define _GameLogic_H_
#include "Player.h"
#include "Stage.h"
#include "Fish.h"
#include <list>
class GameLogic {
  public:
    GameLogic();
    void update(float);
    void handlePlayerDeath(int);
    void handlePlayerCollision();
    void handleBoundaryCollision(int, float);
    void handleFishCollision(int, std::unique_ptr<Fish> &fish);
    void togglePause();
    void returnToMenu();
    void resetGame();
    void handleOptionsMenu();
    void handlePlayerSelectMenu();
    void handleNameTextSubMenu();
    void handleColorSelectSubMenu();
    int getStageProgression();
    void setSFXVolume(float vol);
    void setMusicVolume(float vol);
    float getSFXVolume();
    float getMusicVolume();
    void handlePlayerAttack(int playerNum, sf::Vector2f dir);
    enum GameState {mainMenu, playing, pauseMenu, gameOverMenu, optionsMenu, playerSelectMenu, nameTextSubMenu, colorSelectSubMenu};
    GameState getState();
    int getRound();
    float getRoundTimer();
    bool winner1;
    bool p1_attack_handling_in_progress;
    bool p2_attack_handling_in_progress;
    float player_bump;
    float border_bump;
    float player_hit;
    float splash;
    float powerup;
    Player walrus1;
    Player walrus2;
    Stage stage;
    int round = 1;
    float RoundTimer = 0;

    sf::Vector2f playerCollisionPoint;
    sf::Vector2f p1AttackPoint;
    sf::Vector2f p2AttackPoint;

    std::list<std::unique_ptr<Fish>> fish_list;

private:
    GameState state;
    int progression;
    float accumulator;
    float fish_accumulator;
    float sfx_volume;
    float music_volume;
};

#endif /* _GameLogic_H_ */
