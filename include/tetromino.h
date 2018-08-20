#ifndef TETROMINO_H_
#define TETROMINO_H_

#include "block_printer.h"

class Tetromino {
private:
	static const int SHAPES[7][4][4];
	static const Color COLORS[7];

	int type,
		x,
		y;
	int shape[4][4];
	Color color;
	void *well;

public:
	// Tetromino object constructor;
	Tetromino(void* well);
	// Rotates the tretomino how many times given by parameter (default = 1)
	void rotate(int times = 1);
	// Print the tetromino on the well
	void print(bool onGui = false, int gui_x = 0, int gui_y = 0);
	// Prints the tetromino on GUI at given position (x, y)
	void clear(bool onGui = false, int gui_x = 0, int gui_y = 0);
};

#endif // TETROMINO_H_