#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>

#include "main_menu.h"
#include "endless_mode.h"
#include "credits.h"
#include "scene_master.h"
#include "scene.h"

class Game : public SceneMaster {

  float *scrFactor,
        *widePadding;

  glm::vec2 winOrigDims;

  Scene *currentScene;
  MainMenu *mainMenu;
  EndlessMode *endlessMode;
  Credits *credits;

public:
  Game(const glm::vec2 win_dimentions, float* scrFact, float* wdPadd) {
    winOrigDims = win_dimentions;
    scrFactor = scrFact;
    widePadding = wdPadd;

    mainMenu = new MainMenu(this, win_dimentions, scrFact, wdPadd);
    credits = new Credits(this, win_dimentions, scrFact, wdPadd);
    currentScene = mainMenu;
  }

  ~Game(){
    if (currentScene == endlessMode) {
      delete endlessMode;
    }
    delete mainMenu;
    delete credits;
  }

  void goToMainMenu(){
    if (currentScene == endlessMode) {
      delete endlessMode;
    }
    currentScene = mainMenu;
  }

  void goToEndless(){
    endlessMode = new EndlessMode(this, winOrigDims, scrFactor, widePadding);
    currentScene = endlessMode;
  }

  void goToCredits(){
    currentScene = credits;
  }

  void execute(GLFWwindow *window){
    currentScene->processInputs(window);
    currentScene->update();
    currentScene->draw();
  }
};

#endif