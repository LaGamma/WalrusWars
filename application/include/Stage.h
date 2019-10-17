#ifndef _Stage_H_
#define _Stage_H_

class Stage {
  public:
    Stage();
    void generateMap();
    float getBlockDura(int,int);
    //not doing fish methods for now
  private:
    int stageTiles[40][30];

};

#endif
