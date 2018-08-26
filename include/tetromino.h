#ifndef TETROMINO_H_
#define TETROMINO_H_

#include "field.h"
#include "master.h"
#include "drawer.h"
#include "drawable.h"

class Tetromino : public Drawable{
private:
  static const int DIM = 4;
  static const int TYPES = 7;
  static const unsigned char SHAPES[TYPES][DIM][DIM];

  int type,
    x,
    y;
  unsigned char **shape;
  Field *field;
  Master *master;
  Drawer* drawer;

public:
  // Tetromino object constructor;
  Tetromino(Field* field, Master* master, Drawer* drawer);
  // Tetromino object constructor;
  ~Tetromino();
  // Returns the tretomino shape by reference
  unsigned char** getShape();
  // Returns tretomino's mumber of columns
  int getWidth();
  // Returns tretomino's mumber of rows
  int getHeight();
  // Rotates the tretomino
  void rotate();
  // Print the tetromino on the well
  void print(bool onGui = false, int gui_x = 0, int gui_y = 0);
  // Prints the tetromino on GUI at given position (x, y)
  void clear(bool onGui = false, int gui_x = 0, int gui_y = 0);
};

#endif // TETROMINO_H_