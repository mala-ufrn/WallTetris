#ifndef GAME_MASTER_H
#define GAME_MASTER_H

class GameMaster {
public:
  virtual void createNextTetr(int posX) = 0;
  virtual void increaseScore(int value) = 0;
  virtual void increaseLines(int quantity) = 0;
};

#endif