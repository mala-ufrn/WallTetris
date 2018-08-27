#ifndef BASH_PRINTER_H_
#define BASH_PRINTER_H_

#include <string>
using std::string;
#include <mutex>
using std::mutex;

#include "drawer.h"

class BashPrinter : public Drawer{
private:
  //Printer mutex
  static mutex printerMutex;
  //Piece last x
  int lastX;
  //Piece last y
  int lastY;
  //Piece last shape
  unsigned char** lastShape;
  //active piece reference
  Drawable* lastPiece;
public:
  //Constructor
  BashPrinter();
  //Prints the field border and the ui
  void init(string player, Drawable* field);
  //Updates the game field representation
  void updateField(Drawable* field);
  //Updates the active tetromino drawn on the field
  void updateActivePiece(Drawable* piece, int x, int y);
  //Updates the next tetromino shown on UI
  void updateNext(Drawable* piece);
  //Updates the score shown on UI
  void updateScore(int value);
  //Shows pause message
  void showPause();
  //Shows gameover message
  void showGameOver();
  //Draw method for game loop, EMPTY for bash variation
  void draw(){};
private:
  //Handles TERM signal to restore echo
  static void SignalHandlerFunction (int sig);
  //Print the block on position (x, y) with the selected color
  static void printBlock(int x, int y, int color);
  //Save the cursor position
  static void saveCursor();
  //Restore the cursor position
  static void resumeCursor();
  //Move the cursor position to the (x, y) coordinates
  static void moveCursor(const int x,const int y);
};

#endif //BASH_PRINCER_H_