#include "../include/game_data.h"

#include <iostream>
using std::cout;

#include "../include/block_printer.h"
#include "../include/bash_cursor.h"

void GameData::initDataPane() {
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
}

void GameData::increaseScore(int increaseVal) {
   score += increaseVal;
   BashCursor::save();
   BashCursor::move(4,16);
   cout << "score : " << score;
   BashCursor::resume();
}

void GameData::updateNext(Tetromino* newNext) {
   this->next = newNext;
   newNext->print(true, 14, 7);
}

Tetromino* GameData::getNext() {
   return next;
}

GameData::~GameData() {
   if (next != NULL) {
      delete next;
   }
}