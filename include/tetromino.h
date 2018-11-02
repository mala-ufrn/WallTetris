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
  static const vector<vector<vector<char>>> SHAPES;
  static mutex tetrMutex;

  int type,
      x,
      y;
  vector<vector<char>> shape;
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
  vector<vector<char>> getShape();
private:
  // Computes the active face Check
  static bool outOfBounds(int y, int fieldHeight); 
  // Checks move validity
  static bool dontHasConflict(vector<vector<char>> shape, Field* field, int x, int y);
};

#endif // TETROMINO_H_