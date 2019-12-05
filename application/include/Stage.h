#ifndef _Stage_H_
#define _Stage_H_
#include <SFML/System.hpp>
#include <Definitions.h>

class Stage {
  public:
    Stage() = default;
    void generateMap();
    void tickMelt(int);
    float getTileDura(int,int,int);
  private:
    std::array<std::array<float, ICE_BLOCKS_HEIGHT+2>, ICE_BLOCKS_WIDTH+2> centerStage;
    std::array<std::array<float, ICE_BLOCKS_HEIGHT+2>, ICE_BLOCKS_WIDTH+2> leftStage1;
    std::array<std::array<float, ICE_BLOCKS_HEIGHT+2>, ICE_BLOCKS_WIDTH+2> rightStage1;
    std::array<std::array<float, ICE_BLOCKS_HEIGHT+2>, ICE_BLOCKS_WIDTH+2> leftStage2;
    std::array<std::array<float, ICE_BLOCKS_HEIGHT+2>, ICE_BLOCKS_WIDTH+2> rightStage2;
};

#endif
