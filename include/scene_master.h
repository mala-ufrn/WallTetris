#ifndef SCENE_MASTER_H
#define SCENE_MASTER_H

#include <irrklang/irrKlang.h>

class SceneMaster {
public:
  virtual void goToMainMenu(irrklang::ISound *music = NULL, bool AceptCmd = false) = 0;
  virtual void goToEndless(irrklang::ISound *music) = 0;
  virtual void goToCredits() = 0;
};

#endif