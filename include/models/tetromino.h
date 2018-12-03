#ifndef TETROMINO_H_
#define TETROMINO_H_

#include <vector>
#include <glm/glm.hpp>

#include "models/field.h"
#include "game_master.h"

class Tetromino : public Drawable {
private:
  static const std::vector<std::vector<std::vector<char>>> SHAPES;
  static bool initSeed;

  int type;
  glm::ivec2 pos;

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
  // Checks move validity
  bool dontHasConflict(std::vector<std::vector<char>> testShape, int testX, int testY);
  // Gamble tetromino shape
  static int randType();
};

#endif // TETROMINO_H_