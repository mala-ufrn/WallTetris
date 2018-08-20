#ifndef BLOCK_PRINTER_H_
#define BLOCK_PRINTER_H_

//Colors to printer output
enum Color{
	CLEAR = 0,
	BLACK = 30,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	DEEP_GREEN,
	WHITE
};

class BlockPrinter {
public:
	//Print the block on position (x, y) with the selected color
	static void print(int x, int y, int color);

private:
	BlockPrinter();
};

#endif //BLOCK_PRINCER_H_