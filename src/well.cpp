#include "../include/well.h"

Well::Well(Master *master) {
	this->master = master;

	for (int i = 0; i < 24; ++i) {
		for (int j = 0; j < 12; ++i) {
			if (j == 0 || j == 11 || i == 23) {
				shape[i][j] = 1;
			} else {
				shape[i][j] = 0;
			}
		}
	}
}

void Well::getShape(int shape[24][12]) {
	shape = this->shape;
}

void Well::attachShape(int shape[4][4], Color color, int x, int y) {
	

}

void Well::checkLines() {
	bool flag = false;
	static int count = 0;
	for (int i = 22; i > 0; i--) {
		for (int j = 1; j < 11; j++) {
			if (shape[i][j] == 0) {
				flag = true;
			}
		}
		if (flag == false) {
			//Add points!
			master->increaseScore(100);
			//Down the lines above
			clearLine(i);
			i = i + 1;
		}
		flag = false;
   }
}

void Well::clearLine(int level) {
	int i,j;
	for(i = level; i > 1; i--) {
		for(j = 1; j < 11; j++) {
			shape[i][j] = shape[i - 1][j];
			color[i][j] = color[i - 1][j];
		}
	}
	//Refresh the panel
	for(i = 1; i < 23; i++) {
		for(j = 1; j < 11; j++) {
			if(shape[i][j] == 1) {
				BlockPrinter::print(i, j, color[i][j]);
			}
			if(shape[i][j] == 0) {
				BlockPrinter::print(i, j, CLEAR);
			}
		}
	}
}

void Well::checkGameOver() {
	for (int i = 1; i < 11; ++i)	{
		if (shape[0][i] > 0) {
			master->gameOver();
		}
	}
}