#include "../include/game.h"

Game::Game(Drawer* drawer){
  player = "Player01";
  
  field = new Field(this, drawer);
  nextTetr = NULL;
  activeTetr = NULL;
  this->drawer = drawer;
}

void Game::init() {
  //Starts the score
  score = 0;

  playing = true;
  //draws the start screen;
  drawer->init(player, field);

  //initialize the tetrominoes
  nextTetr = new Tetromino(field, this, drawer);
  createNextTetr();
}

void Game::update() {
  activeTetr->update();
}

bool Game::isPlaying(){
  return playing;
}

void Game::increaseScore(int value) {
  score += value;
  drawer->updateScore(score);
}

void Game::gameOver(){
  drawer->showGameOver();
  playing = false;
}

void Game::createNextTetr() {
  activeTetr = nextTetr;
  nextTetr = new Tetromino(field, this, drawer);
  drawer->updateNext(nextTetr);
  activeTetr->init();
}

Game::~Game() {
  if (nextTetr != NULL) {
    delete nextTetr;
    delete activeTetr;
    delete field;
    delete drawer;
  }
}