#include "../include/block_printer.h"
#include <iostream>
using std::cout;

#include "../include/bash_cursor.h"

void BlockPrinter::print(int x, int y, int color) {
	BashCursor::save();
	BashCursor::move(x,y);
	switch(color)
	{
		case BLACK     : cout << "\033[40;30m  \033[0m"; break;
		case RED       : cout << "\033[41;31m  \033[0m"; break;
		case GREEN     : cout << "\033[42;32m  \033[0m"; break;
		case YELLOW    : cout << "\033[43;33m  \033[0m"; break;
		case BLUE      : cout << "\033[44;34m  \033[0m"; break;
		case PURPLE    : cout << "\033[45;35m  \033[0m"; break;
		case DEEP_GREEN: cout << "\033[46;36m  \033[0m"; break;
		case WHITE     : cout << "\033[47;37m  \033[0m"; break;
		case CLEAR     : cout << "\033[8m  ";
		default: break;
	}
	BashCursor::resume();
}