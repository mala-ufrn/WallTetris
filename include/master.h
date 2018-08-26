#ifndef MASTER_H_
#define MASTER_H_

class Master{
public:
  virtual void increaseScore(int value) = 0;
  virtual void gameOver() = 0;
};

#endif // GAME_MASTER_H_