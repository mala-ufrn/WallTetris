#ifndef WINDOW_PRINTER_H_
#define WINDOW_PRINTER_H_

#include <string>
using std::string;
#include <mutex>
using std::mutex;
#include <vector>

#include "drawer.h"

class WindowPrinter : public Drawer{
private:
  //Height of Wall Tetris
  static int height;
  //Width of Wall Tetris
  static int width;
  //Length of Wall Tetris
  static int length;
  //Angle of horizontal visualization
  static float angle;
  //Matrix of Wall Tetrix
  static std::vector<std::vector<char>> matrix;
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
  WindowPrinter();
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
private:
  //
  static void display();
  //
  static char getColorPosition(int x, int y, int z);
  //
  static void setColor(char color);
};

#endif //WINDOW_PRINTER_H_