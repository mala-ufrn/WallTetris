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
	void *wellRef;

public:
	Tetromino(int x, int y, void* wellRef);
	
};

#endif // TETROMINO_H_