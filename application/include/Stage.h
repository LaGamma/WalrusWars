#ifndef _Stage_H_
#define _Stage_H_

class Stage {
  public:
    Stage();
    void generateMap();
    void tickMelt(float, int);
    float getTileDura(int,int,int);
    //not doing fish methods for now
  private:
    float centerStage[40][30];
    float leftStage1[40][30];
    float leftStage2[40][30];
    float rightStage1[40][30];
    float rightStage2[40][30];

};

#endif
