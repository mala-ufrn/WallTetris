#include "../include/tetromino.h"

#include <stdlib.h>

#include "../include/utils.h"

mutex Tetromino::tetrMutex;

const vector<vector<vector<char>>> Tetromino::SHAPES = {
  //Type I
  {{0, 0, 0, 0}, {'p', 'p', 'p', 'p'}, {0, 0, 0, 0}, {0, 0, 0, 0}},
  //Type J
  {{0, 0, 0, 0}, {'n', 'n', 'n', 0}, {0, 0, 'n', 0}, {0, 0, 0, 0}},
  //Type L
  {{0, 0, 0, 0}, {'r', 'r', 'r', 0}, {'r', 0, 0, 0}, {0, 0, 0, 0}},
  //Type O
  {{0, 0, 0, 0}, {0, 'b', 'b', 0}, {0, 'b', 'b', 0}, {0, 0, 0, 0}},
  //Type S
  {{0, 0, 0, 0}, {0, 'o', 'o', 0}, {'o', 'o', 0, 0}, {0, 0, 0, 0}},
  //Type Z
  {{0, 0, 0, 0}, {'g', 'g', 0, 0}, {0, 'g', 'g', 0}, {0, 0, 0, 0}},
  //Type T
  {{0, 0, 0, 0}, {'y', 'y', 'y', 0}, {0, 'y', 0, 0}, {0, 0, 0, 0}}
};

Tetromino::Tetromino(Field* field, Master* master, Drawer* drawer) {
  this->field = field;
  this->master = master;
  this->drawer = drawer;

  type = Utils::randNum(SHAPES.size()); // Define type

  shape = SHAPES[type];
}

Tetromino::~Tetromino() {}

void Tetromino::init(int xPos){
  x = xPos;
  y = 0;
  //Draw the tetromino on start position
  drawer->updateActivePiece(this, x, y);

  //Check the entry for game over condition
  if(!dontHasConflict(shape, field, x, y)) {
    master->gameOver();
  }
  
  // Stores the clock measure
  clockCheckPoint = clock();
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
  if(dontHasConflict(shape, field, x - 1, y)) {
    x = x == 0? 11 : x-1;
    drawer->updateActivePiece(this, x, y);
  }
  tetrMutex.unlock();
}

void Tetromino::moveRight(){
  tetrMutex.lock();
  if(dontHasConflict(shape, field, x + 1, y)) {
    x = (x+1)%12;
    drawer->updateActivePiece(this, x, y);
  }
  tetrMutex.unlock();
}

void Tetromino::moveDown(){
  tetrMutex.lock();
  if(dontHasConflict(shape, field, x, y + 1)) {
    drawer->updateActivePiece(this, x, ++y);
    tetrMutex.unlock();
  } else {
    field->attachTetromino(shape, x, y);
    tetrMutex.unlock();
    delete this;
  }
}

void Tetromino::rotate() {
  tetrMutex.lock();
  if(type != 3) {
    int d = (type == 0)? 4 : 3;
    vector<vector<char>> rotated(shape.size(), 
                                          vector<char> (shape[0].size(), 0));
    
    for(int i = 0; i < d; i++) {
      for(int j = 0; j < d; j++) {
        rotated[d-1-j][i] = shape[i][j];
      }
    }

    if (dontHasConflict(rotated, field, x, y)){
      shape = rotated;
      drawer->updateActivePiece(this, x, y);
    }
  }
  tetrMutex.unlock();
}

bool Tetromino::dontHasConflict(vector<vector<char>> shape, Field* field, int x, int y) {  
  vector<vector<char>> fShape = field->getShape();
  for(int i = 0; i < shape.size(); i++) {
    for(int j = 0; j < shape[0].size(); j++) {
      if (shape[i][j] != 0 && (outOfBounds(y+i, fShape.size()) || fShape[y+i][(x+j)%12] != 0)) {
        return false;
      }
    }
  }
  return true;
}

bool Tetromino::outOfBounds(int y, int fieldHeight) { 
  return y >= fieldHeight; 
}

vector<vector<char>> Tetromino::getShape() {
  return shape;
}