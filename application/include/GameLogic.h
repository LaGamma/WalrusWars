#ifndef _GameLogic_H_
#define _GameLogic_H_
#include "Player.h"
#include "Stage.h"

class GameLogic {
  public:
    GameLogic();
    void update(float);
    void handlePlayerDeath(int);
    void handlePlayerCollision(

            );
    void togglePause();
    void playGame();
    int getStageProgression();
    enum GameState {mainMenu, playing, pauseMenu, gameOverMenu};
    GameState getState();

    Player walrus1;
    Player walrus2;
    Stage stage;

    sf::Vector2f playerCollisionPoint;

private:
    GameState state;
    int progression;

};

#endif /* _GameLogic_H_ */
