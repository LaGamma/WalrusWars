#ifndef _GameLogic_H_
#define _GameLogic_H_
#include "Player.h"
#include "Stage.h"

class GameLogic {
  public:
    GameLogic();
    void update(float);
    void handlePlayerDeath(int);
    void togglePause();
    void generateMap();
    void playGame();
    enum GameState {mainMenu, playing, pauseMenu, gameOverMenu};
    GameState getState();

  private:
    Player walrus1;
    Player walrus2;
    Stage stage;
    //need to implement the above
    GameState state;

};

#endif /* _GameLogic_H_ */
