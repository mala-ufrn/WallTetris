#include <signal.h>
#include <unistd.h>

#include "../include/game.h"

void SignalHandlerFunction (int sig)
{
	system("stty icanon echo");
	system("clear");
	fflush(stdout);
	kill(getpid(), SIGKILL);
}

int main(int argc, char *argv[]) {
	
	signal(SIGINT, SignalHandlerFunction);
	
	Game *game = new Game();
	system("clear");
	system("stty -icanon -echo");
	
	game->init();

	delete game;
	system("stty icanon echo");
	system("clear");
	return 0;
}