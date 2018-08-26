#include "../include/tetromino.h"

#include <stdlib.h>

#include "../include/utils.h"
#include "../include/bash_printer.h"

const unsigned char Tetromino::SHAPES[TYPES][DIM][DIM] = {
  //Type I
  {{0, 0, 0, 0}, {'b', 'b', 'b', 'b'}, {0, 0, 0, 0}, {0, 0, 0, 0}},
  //Type J
  {{0, 0, 0, 0}, {'b', 'b', 'b', 0}, {0, 0, 'b', 0}, {0, 0, 0, 0}},
  //Type L
  {{0, 0, 0, 0}, {'w', 'w', 'w', 0}, {'w', 0, 0, 0}, {0, 0, 0, 0}},
  //Type O
  {{0, 0, 0, 0}, {0, 'p', 'p', 0}, {0, 'p', 'p', 0}, {0, 0, 0, 0}},
  //Type S
  {{0, 0, 0, 0}, {0, 'p', 'p', 0}, {'p', 'p', 0, 0}, {0, 0, 0, 0}},
  //Type Z
  {{0, 0, 0, 0}, {'y', 'y', 0, 0}, {0, 'y', 'y', 0}, {0, 0, 0, 0}},
  //Type T
  {{0, 0, 0, 0}, {'g', 'g', 'g', 0}, {0, 'g', 0, 0}, {0, 0, 0, 0}}
};

Tetromino::Tetromino(Field* field, Master* master, Drawer* drawer) {
  this->field = field;
  this->master = master;
  this->drawer = drawer;

  x = 4;
  y = 0;

  type = Utils::randNum(TYPES); // Define type

  shape = (unsigned char**)malloc(DIM * sizeof(unsigned char*));
  for (int i = 0; i < DIM; ++i) {
    shape[i] = (unsigned char*)malloc(DIM * sizeof(unsigned char));
    for (int j = 0; j < DIM; ++j) {
      shape[i][j] = SHAPES[type][i][j];
    }
  }
}

Tetromino::~Tetromino() {
  for (int i = 0; i < DIM; ++i) {
    free(shape[i]);
  }
  free(shape);
}

unsigned char** Tetromino::getShape() {
  return shape;
}

int Tetromino::getWidth() {
  return DIM;
}

int Tetromino::getHeight() {
  return DIM;
}

void Tetromino::rotate() {
  if (type != 3) {
    int d = (type == 0)? 4 : 3;
    int b[d][d];
    for(int i = 0; i < d; i++) {
      for(int j = 0; j < d; j++) {
        b[d-1-j][i] = shape[i][j];
      }
    }
    // TO DO Paused here
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
        shape[i][j] = b[i][j];
      }
    }
  }
}