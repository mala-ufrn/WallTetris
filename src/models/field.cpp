#include "models/field.h"

#include <stdlib.h>
#include <iostream>

#define FIELD_NUM_ROWS 19
#define FIELD_NUM_COLS 12

Field::Field(GameMaster *master, irrklang::ISoundEngine* soundEngine) {
  this->master = master;
  this->soundEngine = soundEngine;
  shape = std::vector<std::vector<char>>(FIELD_NUM_ROWS,std::vector<char> (FIELD_NUM_COLS, 0));
}

Field::~Field() {}

void Field::attachTetromino(std::vector<std::vector<char>> tetrShape, int x, int y) {
  for(int i = y; i < y + tetrShape.size(); i++) {
    for(int j = x; j < x + tetrShape[0].size(); j++) {
      if(tetrShape[i-y][j-x] != 0) {
        shape[i][j%FIELD_NUM_COLS] = tetrShape[i-y][j-x];
      }
    }
  }
  master->updateField(this);
  if(checkLines()){
    soundEngine->play2D("res/sounds/bigdrum.wav", false);
  } else {
    soundEngine->play2D("res/sounds/solid.wav", false);
  }
  master->createNextTetr(x);
}

bool Field::checkLines() {
  bool lineComplete = true;
  bool explode = false;
  for (int i = FIELD_NUM_ROWS-1; i > 0; i--) {
    for (int j = 0; j < FIELD_NUM_COLS; j++) {
      if (shape[i][j] == 0) {
        lineComplete = false;
      }
    }
    if (lineComplete) {
      explode = true;
      //Add points!
      master->increaseScore(100);
      master->increaseLines(1);
      //Down the lines above
      clearLine(i);
      i = i + 1;
    }
    lineComplete = true;
   }
   return explode;
}

void Field::clearLine(int level) {
  for(int i = level; i > 1; i--) {
    for(int j = 0; j < FIELD_NUM_COLS; j++) {
      shape[i][j] = shape[i - 1][j];
    }
  }
  master->updateField(this);
}

std::vector<std::vector<char>> Field::getShape() {
  return shape;
}