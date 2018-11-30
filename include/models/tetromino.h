#ifndef TETROMINO_H_
#define TETROMINO_H_

#include <mutex>
#include <vector>

#include "models/field.h"
#include "game_master.h"

class Tetromino{
private:
  static const std::vector<std::vector<std::vector<char>>> SHAPES;
  std::mutex tetrMutex;

  int type,
      x,
      y;
  std::vector<std::vector<char>> shape;
  Field *field;
  GameMaster *master;

public:
  // Tetromino object constructor;
  Tetromino(Field* field, GameMaster* master);
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
  std::vector<std::vector<char>> getShape();
private:
  // Computes the active face Check
  static bool outOfBounds(int y, int fieldHeight); 
  // Checks move validity
  bool dontHasConflict();
};

#endif // TETROMINO_H_