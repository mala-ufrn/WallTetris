#ifndef GAME_H_
#define GAME_H_

#include <string>
using std::string;

#include "master.h"
#include "tetromino.h"
#include "field.h"
#include "drawer.h"

class Game : public Master{
public:
  //Update standard refresh time (ms)
  static const int STD_UPDATE_MSEC;
private:
  //Static reference to current game
  static Game* game;
  //Update current refresh time (ms)
  static bool speedUp;
  //
  static int currentChainNum;
  //Flag for main loop
  bool playing;
  //Flag for pause
  bool paused;
  //Player name
  string player;
  //Player score
  int score;
  //Game field
  Field* field;
  //Next tetromino
  Tetromino* nextTetr;
  //Active tetromino
  Tetromino* activeTetr;
  //Object that draws the game scene
  Drawer* drawer;

public:
  //Constructor for Games objects
  Game(Drawer* drawer);
  //Destructor for Games objects
  ~Game();
  //Change the player atribute
  void setPlayer(string name){player = name;};
  //Prints the start screen and instantiates the initial pieces.
  void init();
  //Main loop execution method
  void update();
  //Returns true if is not game over;
  bool isPlaying();
  //create and show next tetromino
  void createNextTetr(int x);
  //Update and show score increased by parameter value
  void increaseScore(int value);
  //Finish the game
  void gameOver();
  //Static function to controll the game
  static void keyboard(unsigned char key, int x, int y);
  //
  static void keyboardUp(unsigned char key, int x, int y);
  //Static function to access game update funcion
  static void idleFunc(int funcChainNum);
};
#endif // GAME_DATA_H_