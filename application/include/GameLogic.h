#ifndef _GameLogic_H_
#define _GameLogic_H_


class GameLogic {
  public:
    GameLogic();
    void update(float);
    void handlePlayerDeath(int);
    void togglePause();
    void generateMap();
    enum GameState {mainMenu, playing, paused, gameOverMenu};
    GameState getState();

  private:
    // walrus 1: player
    // Walrus 2: player
    // stage: stage
    //need to implement the above

    GameState state;



};

#endif /* _GameLogic_H_ */
