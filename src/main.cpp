#include "../include/game.h"

int main(int argc, char *argv[]) {
	
	Game *game = new Game();
	system("clear");
	system("stty -icanon -echo");

	
	game->init();

	delete game;
	system("stty icanon echo");
	system("clear");
	return 0;
}