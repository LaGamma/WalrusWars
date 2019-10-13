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


  private:
    Player walrus1;
    Player walrus2;
    Stage stage;
    //need to implement the above
    // we also have a gamestate variable, but no gamestate class in the diagram. Do we need one? or should we use ints?




};

#endif /* _GameLogic_H_ */
