#include "../include/game.h"
#include "../include/bash_printer.h"

int main(int argc, char *argv[]) {
  Game *game = new Game(new BashPrinter());
  game->init();
  while(game->isPlaying()) {
    game->update();
  }
  delete game;
  return 0;
}