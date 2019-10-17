#include "Stage.h"

Stage::Stage(){

}

void Stage::generateMap(){
	int i;
	int j;
	for(i = 0; i<40; i++){
		for(j = 0; j<30; j++){
			if((i>1 && i<=39)&&(j>1 && j<=29)){
				stageTiles[i][j] = 1;
			}
			else{
				stageTiles[i][j] = 0;
			} //this is a hardcoded loop that should create an island of ice
		}
	}

}
int Stage::getTile(int x, int y){
	return stageTiles[x][y];
}



float Stage::getBlockDura(int x, int y){
	return 0.0f;
}
