#include "Stage.h"
#include <random>
#include <iostream>

Stage::Stage(){

}

void Stage::generateMap(){
	int i;
	int j;
	for(i = 0; i<40; i++){
		for(j = 0; j<30; j++){
			if((i>8 && i<=32)&&(j>2 && j<=28)){
				centerStage[i][j] = 1;
				if((i>12 && i<=28)&&(j>6&&j<=24)){
					leftStage1[i][j] = 1;
					rightStage1[i][j] = 1;
					if((i>14 && i<=26)&&(j>9&&j<=21)){
						leftStage2[i][j] = 1;
						rightStage2[i][j] = 1;
					}
				}
			}
			else {
			    long r = rand() % 10 + 1;
			    if (r > 6) {
			        centerStage[i][j] = 1;
							leftStage1[i][j] = 1;
							rightStage1[i][j] = 1;
							leftStage2[i][j] = 1;
							rightStage2[i][j] = 1;
			    } else {
			        centerStage[i][j] = 0;
							leftStage1[i][j] = 0;
							rightStage1[i][j] = 0;
							leftStage2[i][j] = 0;
							rightStage2[i][j] = 0;
			    }
			    if (i == 31 || j == 26 || i == 10 || j == 5) {
			        centerStage[i][j] = 0;
			    }


			}
			if(j>13&&j<=17){
				centerStage[i][j] = 1;
				leftStage1[i][j] = 1;
				rightStage1[i][j] = 1;
				if(i>20){
					leftStage2[i][j] = 1;
				}
				if(i<20){
					rightStage2[i][j] = 1;
				}
			} //this is a hardcoded loop that should create an island of ice
		}
	}

}
int Stage::getTile(int x, int y, int stage){
	if(stage == 0){
		return centerStage[x][y];
	}
	else if(stage == -1){
		return leftStage1[x][y];
	}
	if(stage == -2){
		return leftStage2[x][y];
	}
	if(stage == 1){
		return rightStage1[x][y];
	}
	if(stage == 2){
		return rightStage2[x][y];
	}

}



float Stage::getBlockDura(int x, int y){
	return 0.0f;
}
