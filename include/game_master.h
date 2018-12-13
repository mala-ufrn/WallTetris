#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include <glm/glm.hpp>
#include "models/drawable.h"

class GameMaster {
public:
  virtual void createNextTetr(int posX) = 0;
  virtual void increaseScore(int value) = 0;
  virtual void increaseLines(int quantity) = 0;
  virtual void gameOver() = 0;
  virtual void updateField(Drawable *field) = 0;
  virtual void updateActivePiece(Drawable *piece, glm::ivec2 pos) = 0;
  virtual void startExplosion() = 0;
};

#endif