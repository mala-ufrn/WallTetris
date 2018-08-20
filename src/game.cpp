#include "../include/game.h"

#include <iostream>
using std::cout;

#include "../include/block_printer.h"
#include "../include/bash_cursor.h"

void Game::init() {
   score = 0;
   BashCursor::move(0, 5);
   printWell();
   printHud();
   createNextTetr();
}

void Game::printWellBounds() {
   int i;
   for(i = 0; i < 24; i++) {
      BlockPrinter::print(i, 0, BLUE);
      BlockPrinter::print(i, 11, BLUE);
   }
   for(i = 0; i < 12; i++) {
      BlockPrinter::print(23, i, BLUE);
      BlockPrinter::print(0, i, RED);
   }
}

void Game::printHud(){
   // Player name
   BashCursor::save();
   BlockPrinter::print(2, 14, WHITE);
   BashCursor::move(2, 16);
   cout << "player: " << player;
   BashCursor::resume();

   //Score
   BlockPrinter::print(4, 14, GREEN);
   BashCursor::move(4,16);
   cout << "score : " << score;
   BashCursor::resume();

   //NextTetromino
   BashCursor::move(6,14);
   cout << "next : ";
   BashCursor::resume();

   //Help text
   BashCursor::move(12,14);
   cout << "a: go to left\n";
   BashCursor::resume();
   BashCursor::move(13,14);
   cout << "d: go to right";
   BashCursor::resume();
   BashCursor::move(14,14);
   cout << "w: roll cube";
   BashCursor::resume();
   BashCursor::move(15,14);
   cout << "s: go to down";
   BashCursor::resume();
   BashCursor::move(16,14);
   cout << "p: run or pause";
   BashCursor::resume();

   fflush(stdout);
}

void Game::increaseScore(int value) {
   score += value;
   BashCursor::save();
   BashCursor::move(4,16);
   cout << "score : " << score;
   BashCursor::resume();

   fflush(stdout);
}

void Game::createNextTetr() {
   nextTetr = new Tetromino(NULL);
   nextTetr->print(true, 14, 7);
}

Tetromino* Game::getNextTetr() {
   return nextTetr;
}

Game::~Game() {
   if (nextTetr != NULL) {
      delete nextTetr;
   }
}