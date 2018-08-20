#ifndef GAME_DATA_H_
#define GAME_DATA_H_

#include <string>
using std::string;

class GameData;

class GameData{
private:
	//Player name
    string player;
    //Player score;
    int score;

public:
	//Gives the score object reference
	GameData(){player = "Player01";score = 0;};
	//Change the player atribute
    void setPlayer(string name){player = name;};
    //Prints the start score and help text.
    void initDataPane();
    //Update and show score increased by parameter value
    void increaseScore(int increaseVal);
    
};
#endif // GAME_DATA_H_