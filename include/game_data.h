#ifndef GAME_DATA_H_
#define GAME_DATA_H_

#include <string>
using std::string;

#include "tetromino.h"

class GameData;

class GameData{
private:
	//Player name
    string player;
    //Player score
    int score;
    //Next tetromino
    Tetromino* next;

public:
	//Constructor the score object reference
	GameData(){player = "Player01"; score = 0; next == NULL;};
	//Change the player atribute
    void setPlayer(string name){player = name;};
    //Prints the start score and help text.
    void initDataPane();
    //Update and show score increased by parameter value
    void increaseScore(int increaseVal);
    //Update reference and show next tetromino
    void updateNext(Tetromino* newNext);
    //Gives the next tretomino's reference
    Tetromino* getNext();
    //
    ~GameData();
    
};
#endif // GAME_DATA_H_