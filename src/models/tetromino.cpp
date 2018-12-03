#include "models/tetromino.h"

#include <ctime>
#include <stdlib.h>

#include <iostream>

const std::vector<std::vector<std::vector<char>>> Tetromino::SHAPES = {
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

bool Tetromino::initSeed = false;

Tetromino::Tetromino(Field* field, GameMaster* master) {
  this->field = field;
  this->master = master;

  type = randType(); // Define type

  shape = SHAPES[type];
}

Tetromino::~Tetromino() {}

void Tetromino::init(int xPos){
  pos.x = xPos;
  pos.y = 0;
  //Draw the tetromino on start position
  master->updateActivePiece(this, pos);

  //Check the entry for game over condition
  if(!dontHasConflict(shape, pos.x, pos.y)) {
    master->gameOver();
  }
  
  // Stores the clock measure
  //clockCheckPoint = clock();
}

void Tetromino::pause() {
  //pauseOffSet = clock() - clockCheckPoint;
}

void Tetromino::resume() {
  //clockCheckPoint = clock() - pauseOffSet;
  master->updateActivePiece(this, pos);
}

void Tetromino::moveLeft(){

  if(dontHasConflict(shape, pos.x - 1, pos.y)) {
    pos.x = pos.x == 0? 11 : pos.x-1;
    master->updateActivePiece(this, pos);
  }

}

void Tetromino::moveRight(){
  if(dontHasConflict(shape, pos.x + 1, pos.y)) {
    pos.x = (pos.x + 1) % 12;
    master->updateActivePiece(this, pos);
  }
}

void Tetromino::moveDown(){
  if(dontHasConflict(shape, pos.x, pos.y + 1)) {
    pos.y += 1;
    master->updateActivePiece(this, pos);  
  } else {
    field->attachTetromino(shape, pos.x, pos.y); 
    delete this;
  }
}

void Tetromino::rotate() {

  if(type != 3) {
    int d = (type == 0)? 4 : 3;
    std::vector<std::vector<char>> rotated(shape.size(), 
                                 std::vector<char> (shape[0].size(), 0));
    for(int i = 0; i < d; i++) {
      for(int j = 0; j < d; j++) {
        rotated[d-1-j][i] = shape[i][j];
      }
    }

    if (dontHasConflict(rotated, pos.x, pos.y)){
      shape = rotated;
      master->updateActivePiece(this, pos);
    }
  }
}

std::vector<std::vector<char>> Tetromino::getShape() {
  return shape;
}

bool Tetromino::dontHasConflict(std::vector<std::vector<char>> testShape, int testX, int testY){  
  std::vector<std::vector<char>> fShape = field->getShape();
  for(int i = 0; i < testShape.size(); i++) {
    for(int j = 0; j < testShape[0].size(); j++) {
      if (testShape[i][j] != 0 && (testY + i >= fShape.size() || fShape[testY+i][(testX+j)%12] != 0)) {
        return false;
      }
    }
  }
  return true;
}

int Tetromino::randType() {
  
  if (!initSeed){
    srand(unsigned(time(0)));
    initSeed = true;
  }

  return rand() % SHAPES.size();
}