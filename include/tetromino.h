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
  // Velocity in blocks/s
  float fallVelocity;
  Field *field;
  Master *master;
  Drawer* drawer;

public:
  // Tetromino object constructor;
  Tetromino(Field* field, Master* master, Drawer* drawer);
  // Tetromino object constructor;
  ~Tetromino();
  // Prints tetromino and checks the entry
  void init();
  // Stores the clock info
  void pause();
  // Uses clock info to recalculate the fall behavior and draw tetromino
  void resume();
  // Executes the automatic behaviour
  void update();
  // Moves tetromino left if possible
  void moveLeft();
  // Moves tetromino right if possible
  void moveRight();
  // Speeds up tretomino fall
  void speedUp();
  // Rotates the tretomino
  void rotate();
  // Returns the tretomino shape by reference
  unsigned char** getShape();
  // Returns tretomino's mumber of columns
  int getWidth();
  // Returns tretomino's mumber of rows
  int getHeight();
private:
  // Moves tetromino down or attach it to field
  void moveDown();
  // Checks move validity
  static bool dontHasConflict(
      unsigned char** shape, Field* field, int dim, int x, int y);
  // Checks if the block is out of bounds
  static bool outOfBounds(int x, int y, int fieldWidth, int fieldHeight);
};

#endif // TETROMINO_H_