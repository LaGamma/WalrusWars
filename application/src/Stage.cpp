#include "Stage.h"
#include <random>
#include <iostream>
#include <memory>

Stage::Stage(){

}

void Stage::generateMap(){
	int i;
	int j;
	long r;
	for(i = 0; i<40; i++){
		for(j = 0; j<30; j++){
			if((i>8 && i<=32)&&(j>2 && j<=28)){
				centerStage[i][j] = 1;
				leftStage1[i][j] = 1;
				leftStage2[i][j] = 1;
				rightStage1[i][j] = 1;
				rightStage2[i][j] = 1;
				r = rand() % 20;
				if((r>15)&&(((j>2&&j<4)||(j>26&&j<=28))||((i>8&&i<10)||(i>30&&i<=32)))){
					centerStage[i][j] = 0;
				}
				if((r>12)&&(((j>2&&j<6)||(j>24&&j<=28))||((i>8&&i<12)||(i>28&&i<=32)))){
					leftStage1[i][j] = 0;
					rightStage1[i][j] = 0;
				}
				if((r>9)&&(((j>2&&j<8)||(j>22&&j<=28))||((i>8&&i<14)||(i>26&&i<=32)))){
					leftStage2[i][j] = 0;
					rightStage2[i][j] = 0;
				}
				//if((i>10 && i<=30)&&(j>6&&j<=24)){
				//	leftStage1[i][j] = 1;
				//	rightStage1[i][j] = 1;
				//	if((i>12 && i<=28)&&(j>9&&j<=21)){
				//		leftStage2[i][j] = 1;
				//		rightStage2[i][j] = 1;
				//	} //creates the smallest stage
				//} // creates the second-to-last stages
			} // creates the center stage
			else {
			    r = rand() % 10 + 1;
			    if (r > 8) {
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
			    } //adds some random ice bits that 'float' in the sea

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
				} //builds a bridge on each stage
			} //this is a hardcoded loop that should create an island of ice
		}
	}

}

void Stage::tickMelt(float dSec, int stage) {
	// melt the correct stage
	typedef float stage_map[40][30];
	stage_map *melting_stage;
	switch (stage) {
		case -2:
		    melting_stage = &leftStage2;
		    break;
		case -1:
		    melting_stage = &leftStage1;
		    break; 
		case 0:
		    melting_stage = &centerStage;
		    break;
		case 1:
		    melting_stage = &rightStage1;
		    break;
		case 2:
		    melting_stage = &rightStage2;
		    break;
	}

    int r;
	for(int i = 0; i<40; i++) {
		for(int j = 0; j<30; j++) {
			if ((*melting_stage)[i][j] > 0) {
				r = rand() % 100 + 1;
				// only melt 1% of the time to blocks that are not the bridge
				if (r > 99 && (j<=13 || j>17)) {
					// TODO - change uniform melting to melting partially based on neighbors durabilities
					(*melting_stage)[i][j] -= 0.001;
				}
				
			}
		}
	}



}

float Stage::getTileDura(int x, int y, int stage) {
	switch (stage) {
		case -2:
		    return leftStage2[x][y];
		    break;
		case -1:
		    return leftStage1[x][y];
		    break; 
		case 0:
		    return centerStage[x][y];
		    break;
		case 1:
		    return rightStage1[x][y];
		    break;
		case 2:
		    return rightStage2[x][y];
		    break;
	}
}
