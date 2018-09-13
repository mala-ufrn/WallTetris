#ifndef TETROMINO_H_
#define TETROMINO_H_

#include <time.h>
#include <mutex>
using std::mutex;

#include "field.h"
#include "master.h"
#include "drawer.h"

class Tetromino : public Drawable{
private:
  static const int DIM = 4;
  static const int TYPES = 7;
  static const unsigned char SHAPES[TYPES][DIM][DIM];
  static mutex tetrMutex;

  int type,
    x,
    y;
  unsigned char **shape;
  clock_t clockCheckPoint;
  clock_t pauseOffSet;
  Field *field;
  Master *master;
  Drawer* drawer;

public:
  // Tetromino object constructor;
  Tetromino(Field* field, Master* master, Drawer* drawer);
  // Tetromino object constructor;
  ~Tetromino();
  // Prints tetromino and checks the entry
  void init(int xPos);
  // Stores the clock info
  void pause();
  // Uses clock info to recalculate the fall behavior and draw tetromino
  void resume();
  // Moves tetromino left if possible
  void moveLeft();
  // Moves tetromino right if possible
  void moveRight();
  // Moves tetromino down or attach it to field
  void moveDown();
  // Rotates the tretomino
  void rotate();
  // Returns the tretomino shape by reference
  unsigned char** getShape();
  // Returns tretomino's mumber of columns
  int getWidth();
  // Returns tretomino's mumber of rows
  int getHeight();
private:
  // Computes the active face Check
  static bool outOfBounds(int y, int fieldHeight); 
  // Checks move validity
  static bool dontHasConflict(
      unsigned char** shape, Field* field, int dim, int x, int y);
};

#endif // TETROMINO_H_