#ifndef _Stage_H_
#define _Stage_H_

class Stage {
  public:
    Stage();
    void generateMap();
    float getBlockDura(int,int);
    int getTile(int,int, int);
    //not doing fish methods for now
  private:
    int centerStage[40][30];
    int leftStage1[40][30];
    int leftStage2[40][30];
    int rightStage1[40][30];
    int rightStage2[40][30];

};

#endif
