#include "../include/bash_printer.h"

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#define START_X 4
#define START_Y 2

//Colors to printer output
enum Color {
  CLEAR = 0,
  BLACK = 30,
  RED = 114,
  GREEN = 103,
  YELLOW = 121,
  NAIVE_BLUE = 110,
  ORANGE = 111,
  PURPLE = 112,
  BLUE = 98,
  WHITE = 119
};

mutex BashPrinter::printerMutex;

BashPrinter::BashPrinter() {
  lastX = lastY = 0;
  lastShape = NULL;
  lastPiece = NULL;
}

void BashPrinter::init(string player, Drawable* field) {
  //Set handler function
  signal(SIGINT, SignalHandlerFunction);

  system("clear");
  system("stty -icanon -echo");

  printerMutex.lock();
  //Adds left padding
  moveCursor(START_X, START_Y);
  //prints the field bounds
  int height = field->getHeight(),
      width = field->getWidth();

  for(int i = 1; i < height+1; i++) {
    printBlock(0, i, NAIVE_BLUE);
    printBlock(width+1, i, NAIVE_BLUE);
  }
  for(int i = 0; i < width+2; i++) {
    printBlock(i, height, NAIVE_BLUE);
    printBlock(i, 0, RED);
  }

  //prints the UI
  printBlock(field->getWidth()+5, 2, WHITE);
  printBlock(field->getWidth()+5, 4, GREEN);

  //player name
  saveCursor();
  moveCursor(field->getWidth()+7, 2);
  cout << "player: " << player << endl;

  //score
  moveCursor(field->getWidth()+7+START_X, 1);
  cout << "score : 0" << endl;

  //next tetromino label
  moveCursor(field->getWidth()+5+START_X, 1);
  cout << "next : " << endl;

  //help text
  moveCursor(field->getWidth()+5+START_X, 5);
  cout << "a: go to left" << endl;
  moveCursor(field->getWidth()+5+START_X, 0);
  cout << "d: go to right" << endl;
  moveCursor(field->getWidth()+5+START_X, 0);
  cout << "w: roll tetromino" << endl;
  moveCursor(field->getWidth()+5+START_X, 0);
  cout << "s: speed up fall" << endl;
  moveCursor(field->getWidth()+5+START_X, 0);
  cout << "p: pause/resume";
  resumeCursor();

  fflush(stdout);
  printerMutex.unlock();
}

void BashPrinter::updateField(Drawable* field) {
  printerMutex.lock();
  unsigned char** shape = field->getShape();
  for(int i = 1; i < field->getHeight(); i++) {
    for(int j = 0; j < field->getWidth(); j++) {
      printBlock(j + 1, i, shape[i][j]);
    }
  }

  fflush(stdout);
  printerMutex.unlock();
}

void BashPrinter::updateActivePiece(Drawable* piece, int x, int y){
  printerMutex.lock();

  int dimention = piece->getHeight();
  unsigned char** shape = piece->getShape();
  // initialize lastShape
  if(lastShape == NULL){
    lastShape = (unsigned char**)malloc(dimention * sizeof(unsigned char*));
    for (int i = 0; i < dimention; ++i) {
      lastShape[i] = (unsigned char*)malloc(dimention * sizeof(unsigned char));
    }
  }

  // clear on last position/rotation;
  if(piece == lastPiece) {
    for(int i = 0; i < dimention; i++) {
      for(int j = 0; j < dimention; j++) {
        if(lastShape[i][j] != 0) {
          printBlock(lastX + j + 1, lastY + i, CLEAR);
        }
      }
    }
  }
  // draw the piece
  for(int i = 0; i < dimention; i++) {
    for(int j = 0; j < dimention; j++) {
      if (y == 0 && i == 0) {
        lastShape[i][j] = 0;
      } else {
        lastShape[i][j] = shape[i][j];

        if(shape[i][j] != 0) {
          printBlock(x + j + 1, y + i, shape[i][j]);
        }
      }
    }
  }

  fflush(stdout);
  printerMutex.unlock();

  //Memorize last values
  lastPiece = piece;
  lastX = x;
  lastY = y;
}

void BashPrinter::updateNext(Drawable* piece){
  printerMutex.lock();

  //Clears the next area
  for(int i = 0; i < piece->getHeight(); i++) {
    for(int j = 0; j < piece->getWidth(); j++) {
      printBlock(j+15, i+7, CLEAR);
    }
  }
  //Draws the new piece
  unsigned char** shape = piece->getShape();
  for(int i = 0; i < piece->getHeight(); i++) {
    for(int j = 0; j < piece->getWidth(); j++) {
      printBlock(j+15, i+7, shape[i][j]);
    }
  }

  fflush(stdout);
  printerMutex.unlock();
}

void BashPrinter::updateScore(int value) {
  printerMutex.lock();

  saveCursor();
  moveCursor(17, 4);
  cout << "score : " << value;
  resumeCursor();

  fflush(stdout);
  printerMutex.unlock();
}

void BashPrinter::showGameOver(){
  printerMutex.lock();

  saveCursor();
  moveCursor(4,10);
  cout<<"GAME OVER";
  resumeCursor();
  moveCursor(3,11);
  cout<<"Press any key";
  resumeCursor();

  fflush(stdout);
  printerMutex.unlock();

  getchar();
  system("stty icanon echo");
  system("clear");
}

void BashPrinter::showPause(){
  printerMutex.lock();

  saveCursor();
  moveCursor(5,10);
  cout<<"PAUSE";
  resumeCursor();

  fflush(stdout);
  printerMutex.unlock();
}

void BashPrinter::SignalHandlerFunction (int sig)
{
  system("stty icanon echo");
  system("clear");
  fflush(stdout);
  kill(getpid(), SIGTERM);
}

void BashPrinter::printBlock(int x, int y, int color) {
  saveCursor();
  moveCursor(x,y);
  switch(color)
  {
    case BLACK     : cout << "\033[40;30m  \033[0m"; break;
    case RED       : cout << "\033[41;31m  \033[0m"; break;
    case GREEN     : cout << "\033[42;32m  \033[0m"; break;
    case ORANGE    :
    case YELLOW    : cout << "\033[43;33m  \033[0m"; break;
    case NAIVE_BLUE: cout << "\033[44;34m  \033[0m"; break;
    case PURPLE    : cout << "\033[45;35m  \033[0m"; break;
    case BLUE      : cout << "\033[46;36m  \033[0m"; break;
    case WHITE     : cout << "\033[47;37m  \033[0m"; break;
    case CLEAR     : cout << "\033[8m  ";
    default: break;
  }
  resumeCursor();
}

void BashPrinter::saveCursor() {
  //save cur and move to destination
  cout << "\33[s";
}

void BashPrinter::resumeCursor() {
  cout << "\33[u";
}

void BashPrinter::moveCursor(const int x,const int y) {
  int i;
  for(i = 0; i < x; i++) {
    cout << "\33[2C";
  }
  for(i = 0; i < y; i++) {
    cout << "\33[1B";
  }
}