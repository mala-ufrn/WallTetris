#ifndef GAME_H_
#define GAME_H_

#include <string>
using std::string;
#include <thread>
using std::thread;

#include "master.h"
#include "tetromino.h"
#include "field.h"
#include "drawer.h"

class Game : public Master{
private:
  //Static reference to current game
  static Game* game;
  //Flag for main loop
  bool playing;
  //Flag for bash version
  bool isBash;
  //Flag for pause
  bool paused;
  //Player name
  string player;
  //Player score
  int score;
  //Face in front
  int activeFace;
  //Game field
  Field* field;
  //Next tetromino
  Tetromino* nextTetr;
  //Active tetromino
  Tetromino* activeTetr;
  //Object that draws the game scene
  Drawer* drawer;
  // Thread for inputs listen
  thread* controller;

public:
  //Constructor for Games objects
  Game(Drawer* drawer);
  //Destructor for Games objects
  ~Game();
  //Change the player atribute
  void setPlayer(string name){player = name;};
  //Prints the start screen and instantiates the initial pieces.
  void init(bool isBash=false);
  //Main loop execution method
  void update();
  //Returns true if is not game over;
  bool isPlaying();
  //create and show next tetromino
  void createNextTetr();
  //Update and show score increased by parameter value
  void increaseScore(int value);
  //Sets the wall active face
  void setActiveFace(int face);
  //Finish the game
  void gameOver();
  //Static function to controll the game
  static void keyboard(unsigned char key, int x, int y);
  //Static function to access game update funcion
  static void idleFunc();
private:
  void listenKeys();
};
#endif // GAME_DATA_H_