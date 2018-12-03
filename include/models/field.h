#ifndef FIELD_H_
#define FIELD_H_

#include <vector>

#include "game_master.h"

class Field : public Drawable {
private:
  std::vector<std::vector<char>> shape;
  GameMaster* master;

public:
  // Well object constructor;
  Field(GameMaster *master);
  // Well object destructor;
  ~Field();
  // Returns the field shape by reference
  std::vector<std::vector<char>> getShape();
  // Attach the piece of shape at given position (x, y)
  void attachTetromino(std::vector<std::vector<char>> tetrShape, int x, int y);
private:
  // Check if there are complete lines
  void checkLines();
  // Clear the referenced line and down the uppers
  void clearLine(int level);
};

#endif //FIELD_H_