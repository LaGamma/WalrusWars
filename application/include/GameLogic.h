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
    void togglePause();
    void returnToMenu();
    void resetGame();
    int getStageProgression();
    enum GameState {mainMenu, playing, pauseMenu, gameOverMenu};
    GameState getState();
    bool winner1;
    int bump;
    int splash;
    Player walrus1;
    Player walrus2;
    Stage stage;

    sf::Vector2f playerCollisionPoint;
    std::list<std::unique_ptr<Fish>> fish_list;

private:
    GameState state;
    int progression;
    float accumulator;
};

#endif /* _GameLogic_H_ */
