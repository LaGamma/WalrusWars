#ifndef _GameLogic_H_
#define _GameLogic_H_
#include "Player.h"
#include "Stage.h"

class GameLogic {
  public:
    GameLogic();
    void update(float);
    void handlePlayerDeath(int);
    void handlePlayerCollision();
    void togglePause();
    void playGame();
    int getStageProgression();
    enum GameState {mainMenu, playing, pauseMenu, gameOverMenu};
    GameState getState();
    bool winner1;
	bool reset_sprite;
    Player walrus1;
    Player walrus2;
    Stage stage;

    sf::Vector2f playerCollisionPoint;

private:
    GameState state;
    int progression;
    float accumulator;
};

#endif /* _GameLogic_H_ */
