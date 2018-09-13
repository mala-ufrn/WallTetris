#include "../include/game.h"

Game* Game::game;

Game::Game(Drawer* drawer){
  player = "Player01";
  
  field = new Field(this, drawer);
  nextTetr = NULL;
  activeTetr = NULL;
  this->drawer = drawer;
}

void Game::init() {
  game = this;
  //Starts the score
  score = 0;
  playing = true;
  paused = false;
  //draws the start screen;
  drawer->init(player, field);

  //initialize the tetrominoes
  nextTetr = new Tetromino(field, this, drawer);
  createNextTetr(0);
}

void Game::update() {
  if(!paused) {
    activeTetr->update();
  }
}

bool Game::isPlaying(){
  return playing;
}

void Game::increaseScore(int value) {
  score += value;
  drawer->updateScore(score);
}

void Game::gameOver(){
  playing = false;
  drawer->showGameOver();
}

void Game::createNextTetr(int x) {
  activeTetr = nextTetr;
  nextTetr = new Tetromino(field, this, drawer);
  drawer->updateNext(nextTetr);
  activeTetr->init(x);
}

void Game::keyboard(unsigned char key, int x, int y) {
  if (game->paused && key != 'p' && key != 'q') return;
  switch(key) {
    case 'a':
      game->activeTetr->moveLeft();
      break;
    case 'd':
      game->activeTetr->moveRight();
      break;
    case 'w':
      game->activeTetr->rotate();
      break;
    case 's':
      game->activeTetr->speedUp();
      break;
    case 'p':
      if(game->paused) {
        game->paused = false;
        game->drawer->updateField(game->field);
        game->activeTetr->resume();
      } else {
        game->paused = true;
        game->drawer->showPause();
        game->activeTetr->pause();
      }
      break;
    case 'q':
        exit(-1);
    default:
      break;
  }
}

void Game::idleFunc(){
  if(game->isPlaying()) {
    game->update(); 
  }
}

void Game::listenKeys() {
  while(playing) {
    keyboard(getchar(),0,0);
  }
}

Game::~Game() {
  if (nextTetr != NULL) {
    delete nextTetr;
    delete activeTetr;
    delete field;
    delete drawer;
  }
}