#ifndef DRAWER_H_
#define DRAWER_H_

#include <string>
using std::string;

#include "drawable.h"

class Drawer{
public:
  virtual void init(string player, Drawable* field) = 0;
  virtual void updateField(Drawable* field) = 0;
  virtual void updateActivePiece(Drawable* piece, int x, int y) = 0;
  virtual void updateScore(int value) = 0;
  virtual void updateNext(Drawable* piece) = 0;
  virtual void showPause() = 0;
  virtual void showGameOver() = 0;
};

#endif // DRAWER_H_