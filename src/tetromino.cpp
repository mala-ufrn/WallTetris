#include "../include/tetromino.h"

#include <stdlib.h>

#include "../include/utils.h"
#include "../include/bash_printer.h"

#define NORMAL_VEL 1.5
#define SPEED_UP_VEL 15

mutex Tetromino::tetrMutex;

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

  x = 3;
  y = 0;

  type = Utils::randNum(TYPES); // Define type
  fallVelocity = NORMAL_VEL;

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

void Tetromino::init(){
  //Draw the tetromino on start position
  drawer->updateActivePiece(this, x, y);

  //Check the entry for game over condition
  if(!dontHasConflict(shape, field, DIM, x, y)) {
    master->gameOver();
  }
  
  // Stores the clock measure
  clockCheckPoint = clock();
}

void Tetromino::update() {

  float elapsedTime = 
      ((float)(clock() - clockCheckPoint)) / CLOCKS_PER_SEC;
  if (elapsedTime >= 1 / fallVelocity) {
    moveDown();
    clockCheckPoint = clock();
    fallVelocity = NORMAL_VEL;
  }
}

void Tetromino::pause() {
  pauseOffSet = clock() - clockCheckPoint;
}

void Tetromino::resume() {
  clockCheckPoint = clock() - pauseOffSet;
  drawer->updateActivePiece(this, x, y);
}

void Tetromino::moveLeft(){
  tetrMutex.lock();
  if(dontHasConflict(shape, field, DIM, x - 1, y)) {
    drawer->updateActivePiece(this, --x, y);
  }
  tetrMutex.unlock();
}

void Tetromino::moveRight(){
  tetrMutex.lock();
  if(dontHasConflict(shape, field, DIM, x + 1, y)) {
    drawer->updateActivePiece(this, ++x, y);
  }
  tetrMutex.unlock();
}

void Tetromino::moveDown(){
  tetrMutex.lock();
  if(dontHasConflict(shape, field, DIM, x, y + 1)) {
    drawer->updateActivePiece(this, x, ++y);
    tetrMutex.unlock();
  } else {
    field->attachTetrShape(shape, DIM, x, y);
    tetrMutex.unlock();
    delete this;
  }
}

void Tetromino::speedUp(){
  fallVelocity = SPEED_UP_VEL;
}

void Tetromino::rotate() {
  tetrMutex.lock();
  if(type != 3) {
    int d = (type == 0)? 4 : 3;
    unsigned char** b = (unsigned char**)malloc(d * sizeof(unsigned char*));
    for(int i = 0; i < d; i++) {
      b[i] = (unsigned char*)malloc(d * sizeof(unsigned char));
    }
    for(int i = 0; i < d; i++) {
      for(int j = 0; j < d; j++) {
        b[d-1-j][i] = shape[i][j];
      }
    }

    bool commit = dontHasConflict(b, field, d, x, y);
    for(int i = 0; i < d; i++) {
      for(int j = 0; j < d; j++) {
        if (commit){
          shape[i][j] = b[i][j];
        }
      }
      free(b[i]);
    }
    free(b);
    if(commit){
      drawer->updateActivePiece(this, x, y);
    }
  }
  tetrMutex.unlock();
}

bool Tetromino::dontHasConflict(
    unsigned char** shape, Field* field, int dim, int x, int y) {
  unsigned char** fShape = field->getShape();
  int fw = field->getWidth();
  int fh = field->getHeight();
  for(int i = 0; i < dim; i++) {
    for(int j = 0; j < dim; j++) {
      if (shape[i][j] != 0 && 
          (outOfBounds(x+j, y+i, fw, fh) || fShape[y+i][x+j] != 0)) {
        return false;
      }
    }
  }
  return true;
}

bool Tetromino::outOfBounds(int x, int y, int fieldWidth, int fieldHeight) {
  return x < 0 || x >= fieldWidth || y >= fieldHeight;
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