#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>

#include "main_menu.h"
#include "scene_master.h"
#include "scene.h"

class Game : public SceneMaster {

  float *scrFactor,
        *widePadding;

  glm::vec2 winOrigDims;

  Scene *currentScene;
  MainMenu *mainMenu;

public:
  Game(const glm::vec2 win_dimentions, float* scrFact, float* wdPadd) {
    mainMenu = new MainMenu(win_dimentions, scrFact, wdPadd);
    currentScene = mainMenu;

    winOrigDims = win_dimentions;
    scrFactor = scrFact;
    widePadding = wdPadd;
  }

  ~Game(){
    delete mainMenu;
  }

  void goToMainMenu(){}

  void goToEndless(){}

  void goToCredits(){}

  void execute(){
    currentScene->processInputs();
    currentScene->update();
    currentScene->draw();
  }
};

#endif