#ifndef WELL_H_
#define WELL_H_

#include "master.h"
#include "block_printer.h"

class Well {
private:
	int shape[24][12];
	Color color[24][12];
	Master *master;

public:
	// Well object constructor;
	Well(Master *master);
	// Returns the well shape by reference
	void getShape(int shape[24][12]);
	// Attach the piece of shape at given position (x, y)
	void attachShape(int shape[4][4], Color color, int x, int y);
private:
	// Check if there are complete lines
	void checkLines();
	// Clear the referenced line and down the uppers
	void clearLine(int level);
	// Check the GameOver condition (Touch the Ceil)
	void checkGameOver();
};

#endif //WELL_H_