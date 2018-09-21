#ifndef GLUT_DRAWER_H_
#define GLUT_DRAWER_H_

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "drawer.h"
#include "game.h"

class GlutDrawer : public Drawer{
public:
  // camera roll refresh time (ms)
  static const int CAMERA_REFRESH_MSEC;
private:
  //Static reference to current drawer
  static GlutDrawer* drawer;
  //Height of Wall Tetris
  int height;
  //Width of Wall Tetris
  int width;
  //Length of Wall Tetris
  int length;
  //Angle of horizontal visualization
  float horAngle;
  //Player name
  char playerLabel[60];
  //Player score
  char scoreLabel[20];
  //Matrix of Wall Tetrix
  vector<vector<char>> fieldMatrix;
  //Matrix of Next Tetromino
  char next[4][4];
  //Piece last x
  int lastX;
  //Piece last y
  int lastY;
  //Piece last shape
  unsigned char** lastShape;
  //active piece reference
  Drawable* lastPiece;
  //
  bool paused;
  //
  bool finished;
public:
  //Constructor
  GlutDrawer();
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
  void switchPause(bool paused);
  //Shows gameover message
  void showGameOver();
  // 
  static void display();
  //
  static void rollCamera(int value);
private:
  //
  static char getColorPosition(int x, int y, int z);
  //
  static void setColor(char color);
};

#endif //WINDOW_PRINTER_H_
