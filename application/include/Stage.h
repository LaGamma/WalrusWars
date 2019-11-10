#ifndef _Stage_H_
#define _Stage_H_
#include <SFML/System.hpp>

class Stage {
  public:
    Stage();
    void generateMap();
    void tickMelt(int);
    float getTileDura(int,int,int);
    //not doing fish methods for now
    sf::Vector2f getFishBounds(int);
  private:
    float centerStage[40][30];
    float leftStage1[40][30];
    float leftStage2[40][30];
    float rightStage1[40][30];
    float rightStage2[40][30];

};

#endif
