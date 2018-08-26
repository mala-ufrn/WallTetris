#ifndef FIELD_H_
#define FIELD_H_

#include "master.h"
#include "drawer.h"
#include "drawable.h"

class Field : public Drawable {
private:
  unsigned char** shape;
  Master* master;
  Drawer* drawer;

public:
  // Well object constructor;
  Field(Master *master, Drawer* drawer);
  // Well object destructor;
  ~Field();
  // Returns the field shape by reference
  unsigned char** getShape();
  // Returns field's mumber of columns
  int getWidth();
  // Returns field's mumber of rows
  int getHeight();
  // Attach the piece of shape at given position (x, y)
  void attachTetrShape(unsigned char** tetrShape, int dim, int x, int y);
  // Prints the well
  void print();
private:
  // Check if there are complete lines
  void checkLines();
  // Clear the referenced line and down the uppers
  void clearLine(int level);
};

#endif //FIELD_H_