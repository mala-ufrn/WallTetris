#include "../include/block_printer.h"
#include "../include/bash_cursor.h"
#include "../include/game_data.h"

int main(int argc, char *argv[]) {
	
	GameData *gData = new GameData();
	system("clear");
	system("stty -icanon -echo");

	BashCursor::move(0, 5);
	int i;
	for(i = 0; i < 24; i++)	{
		BlockPrinter::print(i, 0, BLUE);
		BlockPrinter::print(i, 11, BLUE);
	}
	for(i = 0; i < 12; i++) {
		BlockPrinter::print(23, i, BLUE);
		BlockPrinter::print(0, i, RED);
	}
	gData->initDataPane();
	fflush(stdout);

	gData->updateNext(new Tetromino(NULL));
	fflush(stdout);

	delete gData;
	system("stty icanon echo");
	system("clear");
	return 0;
}