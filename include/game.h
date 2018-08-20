#ifndef GAME_H_
#define GAME_H_

#include <string>
using std::string;

#include "master.h"
#include "tetromino.h"

class Game : public Master{
private:
	//Player name
    string player;
    //Player score
    int score;
    //Next tetromino
    Tetromino* nextTetr;

public:
	//Constructor the score object reference
	Game(){player = "Player01";};
	//Change the player atribute
    void setPlayer(string name){player = name;};
    //Prints the GUI.
    void init();
    //Prints the Score and Help
    void printHud();
    //Prints the Well boundiary
    void printWellBounds();
    //Update and show score increased by parameter value
    void increaseScore(int value);
    //Finish the game
    void gameOver(){};
    //create and show next tetromino
    void createNextTetr();
    //Gives the next tretomino's reference
    Tetromino* getNextTetr();
    //
    ~Game();
    
};
#endif // GAME_DATA_H_