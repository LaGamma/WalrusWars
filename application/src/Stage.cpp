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
			if((i>10 && i<=30)&&(j>5 && j<=25)){
				centerStage[i][j] = 1;
			}
			else if((i>14 && i<=26)&&(j>9&&j<=21)){
				leftStage1[i][j] = 1;
				rightStage1[i][j] = 1;
			}
			else if((i>16 && i<=24)&&(j>11&&j<=19)){
				leftStage2[i][j] = 1;
				rightStage2[i][j] = 1;
			}
			else if((j>13&&j<=17)){
				centerStage[i][j] = 1;
				leftStage1[i][j] = 1;
				rightStage1[i][j] = 1;
			}
			else if((j>13&&j<=17)&&(i>20)){
				leftStage2[i][j] = 1;
			}
			else if((j>13&&j<=17)&&(i<20)){
				rightStage2[i][j] = 1;
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
		std::cout<<centerStage[i][j]; //this is a hardcoded loop that should create an island of ice
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
