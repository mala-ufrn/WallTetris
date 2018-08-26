#include "../include/field.h"

#include <stdlib.h>

#include "../include/bash_printer.h"

#define FIELD_NUM_ROWS 21
#define FIELD_NUM_COLS 10

Field::Field(Master *master, Drawer* drawer) {
  this->master = master;
  this->drawer = drawer;
  
  shape = (unsigned char**)malloc(FIELD_NUM_ROWS *sizeof(unsigned char*));

  for (int i = 0; i < FIELD_NUM_ROWS; ++i) {
    shape[i] = (unsigned char*)malloc(FIELD_NUM_COLS * sizeof(unsigned char));
    for (int j = 0; j < FIELD_NUM_COLS; ++j){
      shape[i][j] = 0;
    }
  }
}

Field::~Field() {
  for (int i = 0; i < FIELD_NUM_ROWS; ++i) {
    free(shape[i]);
  }
  free(shape);
}

void Field::attachTetrShape(unsigned char** tetrShape, int dim, int x, int y) {
  // TO DO
}

void Field::checkLines() {
  bool flag = false;
  for (int i = 22; i > 0; i--) {
    for (int j = 1; j < 11; j++) {
      if (shape[i][j] == 0) {
        flag = true;
      }
    }
    if (flag == false) {
      //Add points!
      master->increaseScore(100);
      //Down the lines above
      clearLine(i);
      i = i + 1;
    }
    flag = false;
   }
}

void Field::clearLine(int level) {
  for(int i = level; i > 1; i--) {
    for(int j = 1; j < 11; j++) {
      shape[i][j] = shape[i - 1][j];
    }
  }
  drawer->updateField(this);
}

unsigned char** Field::getShape() {
  return shape;
}

int Field::getWidth() {
  return FIELD_NUM_COLS;
}

int Field::getHeight() {
  return FIELD_NUM_ROWS;
}