#ifndef _Stage_H_
#define _Stage_H_
#include <SFML/System.hpp>
#include <Definitions.h>

class Stage {
  public:
    Stage();
    void generateMap();
    void tickMelt(int);
    float getTileDura(int,int,int);
  private:
    float centerStage[ICE_BLOCKS_WIDTH+2][ICE_BLOCKS_HEIGHT+2];
    float leftStage1[ICE_BLOCKS_WIDTH+2][ICE_BLOCKS_HEIGHT+2];
    float leftStage2[ICE_BLOCKS_WIDTH+2][ICE_BLOCKS_HEIGHT+2];
    float rightStage1[ICE_BLOCKS_WIDTH+2][ICE_BLOCKS_HEIGHT+2];
    float rightStage2[ICE_BLOCKS_WIDTH+2][ICE_BLOCKS_HEIGHT+2];

};

#endif
