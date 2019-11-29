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
	for(i = -1; i < ICE_BLOCKS_WIDTH+1; i++){
		for(j = -1; j < ICE_BLOCKS_HEIGHT+1; j++){
			if((i>8*ICE_BLOCKS_WIDTH/40 && i<=32*ICE_BLOCKS_WIDTH/40) && (j>2*ICE_BLOCKS_HEIGHT/30 && j<=28*ICE_BLOCKS_HEIGHT/30)){
				centerStage[i][j] = 1;
				leftStage1[i][j] = 1;
				leftStage2[i][j] = 1;
				rightStage1[i][j] = 1;
				rightStage2[i][j] = 1;
				r = rand() % 20;
				if((r>15)&&(((j>2*ICE_BLOCKS_HEIGHT/30&&j<4*ICE_BLOCKS_HEIGHT/30)||(j>26*ICE_BLOCKS_HEIGHT/30&&j<=28*ICE_BLOCKS_HEIGHT/30))
				        ||((i>8*ICE_BLOCKS_WIDTH/40&&i<10*ICE_BLOCKS_WIDTH/40)||(i>30*ICE_BLOCKS_WIDTH/40&&i<=32*ICE_BLOCKS_WIDTH/40)))){
					centerStage[i][j] = 0;
				}
				if((r>12)&&(((j>2*ICE_BLOCKS_HEIGHT/30&&j<6*ICE_BLOCKS_HEIGHT/30)||(j>24*ICE_BLOCKS_HEIGHT/30&&j<=28*ICE_BLOCKS_HEIGHT/30))
				        ||((i>8*ICE_BLOCKS_WIDTH/40&&i<12*ICE_BLOCKS_WIDTH/40)||(i>28*ICE_BLOCKS_WIDTH/40&&i<=32*ICE_BLOCKS_WIDTH/40)))) {
					leftStage1[i][j] = 0;
					rightStage1[i][j] = 0;
				}
				if((r>9)&&(((j>2*ICE_BLOCKS_HEIGHT/30&&j<8*ICE_BLOCKS_HEIGHT/30)||(j>22*ICE_BLOCKS_HEIGHT/30&&j<=28*ICE_BLOCKS_HEIGHT/30))
				        ||((i>8*ICE_BLOCKS_WIDTH/40&&i<14*ICE_BLOCKS_WIDTH/40)||(i>26*ICE_BLOCKS_WIDTH/40&&i<=32*ICE_BLOCKS_WIDTH/40)))){
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
			    if (i == (int)31*ICE_BLOCKS_WIDTH/40 || j == (int)26*ICE_BLOCKS_HEIGHT/30 || i == (int)10*ICE_BLOCKS_WIDTH/40 || j == (int)5*ICE_BLOCKS_HEIGHT/30) {
			        centerStage[i][j] = 0;
			    } //adds some random ice bits that 'float' in the sea

			}
			if(j>13*ICE_BLOCKS_HEIGHT/30&&j<=17*ICE_BLOCKS_HEIGHT/30){
				centerStage[i][j] = 1;
				leftStage1[i][j] = 1;
				rightStage1[i][j] = 1;
				if(i>20*ICE_BLOCKS_WIDTH/40){
					leftStage2[i][j] = 1;
				}
				if(i<20*ICE_BLOCKS_WIDTH/40){
					rightStage2[i][j] = 1;
				} //builds a bridge on each stage
			} //this is a hardcoded loop that should create an island of ice
		}
	}

}

void Stage::tickMelt(int stage) {
	// melt the correct stage
	typedef float stage_map[ICE_BLOCKS_WIDTH+2][ICE_BLOCKS_HEIGHT+2];
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
	float sum;
	int r;
	for(int i = 0; i < ICE_BLOCKS_WIDTH+1; i++) {
		for(int j = 0; j < ICE_BLOCKS_HEIGHT+1; j++) {
			if ((*melting_stage)[i][j] > 0) {
				r = rand() % 100 + 1;
				sum = (*melting_stage)[i-1][j] + (*melting_stage)[i+1][j] + (*melting_stage)[i-1][j-1] + (*melting_stage)[i-1][j+1] + (*melting_stage)[i+1][j-1] + (*melting_stage)[i+1][j+1] + (*melting_stage)[i][j+1]+ (*melting_stage)[i][j-1];
				if(sum>=6){
					if(r > 99 && (j<=13*ICE_BLOCKS_HEIGHT/30 || j>17*ICE_BLOCKS_HEIGHT/30)){
						(*melting_stage)[i][j] -= .05;
					}
				}
				else if(sum<6&&sum>=4){
					if(r > 60 && (j<=13*ICE_BLOCKS_HEIGHT/30 || j>17*ICE_BLOCKS_HEIGHT/30)){
						(*melting_stage)[i][j] -= .05;
					}
				}
				else if(sum<4&&sum>=2){
					if(r > 30 && (j<=13*ICE_BLOCKS_HEIGHT/30 || j>17*ICE_BLOCKS_HEIGHT/30)){
						(*melting_stage)[i][j] -= .05;
					}
				}
				else{
					if(r > 10 && (j<=13*ICE_BLOCKS_HEIGHT/30 || j>17*ICE_BLOCKS_HEIGHT/30)){
						(*melting_stage)[i][j] -= .05;
					}
				}
				// now melts based off a sum of neighbor values
				//for example, an iceblock with neighbor iceblocks that haven't melted as much is less likely to melt
				// an ice block whose neighbors have all melted away is more likely to melt

			}
		}
	}



}

float Stage::getTileDura(int x, int y, int stage) {
	switch (stage) {
		case -2:
		    return leftStage2[x][y];
		case -1:
		    return leftStage1[x][y];
		case 0:
		    return centerStage[x][y];
		case 1:
		    return rightStage1[x][y];
		case 2:
		    return rightStage2[x][y];
	}
}
