#include "../include/field.h"

#include <stdlib.h>
#include <iostream>

#define FIELD_NUM_ROWS 19
#define FIELD_NUM_COLS 12

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
  for(int i = y; i < y + dim; i++) {
    for(int j = x; j < x + dim; j++) {
      if(tetrShape[i-y][j-x] != 0) {
        shape[i][j%FIELD_NUM_COLS] = tetrShape[i-y][j-x];
      }
    }
  }
  drawer->updateField(this);
  checkLines();
  master->createNextTetr(x);
}

void Field::checkLines() {
  bool lineComplete = true;
  for (int i = FIELD_NUM_ROWS-1; i > 0; i--) {
    for (int j = 0; j < FIELD_NUM_COLS; j++) {
      if (shape[i][j] == 0) {
        lineComplete = false;
      }
    }
    if (lineComplete) {
      //Add points!
      master->increaseScore(100);
      //Down the lines above
      clearLine(i);
      i = i + 1;
    }
    lineComplete = true;
   }
}

void Field::clearLine(int level) {
  for(int i = level; i > 1; i--) {
    for(int j = 0; j < FIELD_NUM_COLS; j++) {
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