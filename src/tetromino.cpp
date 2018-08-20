#include "../include/tetromino.h"

#include <string.h>

#include "../include/utils.h"

const int Tetromino::SHAPES[7][4][4] = {
	//Type I
	{{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},
	//Type J
	{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	//Type L
	{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	//Type O
	{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	//Type S
	{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	//Type Z
	{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	//Type T
	{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
};

const Color Tetromino::COLORS[7] = {
	DEEP_GREEN, DEEP_GREEN, WHITE, PURPLE, PURPLE, YELLOW, GREEN
};

Tetromino::Tetromino(void* well) {
	this->well = well;

	x = 4;
	y = 1;

	type = Utils::randNum(7); // Define type
	int rot = Utils::randNum(4); // Define initial rotation

	memcpy(shape, SHAPES[type], 16 * sizeof(int));
	color = COLORS[type];

	if (rot > 0){
		rotate(rot);
	}

	if (rot == 2 && type != 0 && type != 3) {
		y -= 1;
	} else if (type == 0){
		y-= rot == 1? 2 : rot == 2? 1 : 0;
	}
}

void Tetromino::rotate(int times) {

	if(type == 0) {
		int i, j;
	    int b[4][4];
	    for(i = 0; i < 4; i++) {
	        for(j = 0; j < 4; j++) {
	            b[3-j][i] = shape[i][j];
	        }
	    }
	    for(i = 0; i < 4; i++) {
	        for(j = 0; j < 4; j++) {
	            shape[i][j] = b[i][j];
	        }
	    }
	} else if (type != 3) {
		int i, j;
	    int b[3][3];
	    for(i = 0; i < 3; i++) {
	        for(j = 0; j < 3; j++) {
	            b[2-j][i] = shape[i][j];
	        }
	    }
	    for(i = 0; i < 3; i++) {
	        for(j = 0; j < 3; j++) {
	            shape[i][j] = b[i][j];
	        }
	    }
    }
}

void Tetromino::print(bool onGui, int gui_x, int gui_y) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(shape[i][j] == 1) {
            	if (onGui) {
	            	BlockPrinter::print(gui_y + i, gui_x + j, color);
	            }
	            else {
	            	BlockPrinter::print(y + i, x + j, color);
	            }
            }
        }
    }
}

void Tetromino::clear(bool onGui, int gui_x, int gui_y) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(shape[i][j] == 1) {
            	if (onGui) {
	            	BlockPrinter::print(gui_y + i, gui_x + j, CLEAR);
	            }
	            else {
	            	BlockPrinter::print(y + i, x + j, CLEAR);
	            }
            }
        }
    }
}