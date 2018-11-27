#ifndef SCENE_MASTER_H
#define SCENE_MASTER_H

class SceneMaster {
public:
  virtual void goToMainMenu() = 0;
  virtual void goToEndless() = 0;
  virtual void goToCredits() = 0;
};

#endif