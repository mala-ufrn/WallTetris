#include "../include/game.h"

#include <GL/glut.h>

Game* Game::game;

const int Game::STD_UPDATE_MSEC = 4 * 1000 / 7; // 7 blocks per 4 seconds

bool Game::speedUp = false;
int Game::upTimerThreadNum = 0;

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
    activeTetr->moveDown();
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
      speedUp = true;
      glutIgnoreKeyRepeat(1);
      glutTimerFunc(1 ,idleFunc, ++upTimerThreadNum);
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

void Game::keyboardUp(unsigned char key, int x, int y) {
  switch(key) {
    case 's':
      speedUp = false;
      glutIgnoreKeyRepeat(0);
      glutTimerFunc(STD_UPDATE_MSEC / 5 ,idleFunc, ++upTimerThreadNum);
    default:
      break;
  }
}

void Game::idleFunc(int value){
  if(game->isPlaying()) {
    if (value == upTimerThreadNum){
      game->update();
      int refreshTime = speedUp? STD_UPDATE_MSEC / 10 : STD_UPDATE_MSEC;
      glutTimerFunc(refreshTime ,idleFunc, value);
    }
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