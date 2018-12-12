#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>

#include "scenes/main_menu.h"
#include "scenes/endless_mode.h"
#include "scenes/credits.h"
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
  irrklang::ISoundEngine *soundEngine;

public:
  Game(const glm::vec2 win_dimentions, float* scrFact, float* wdPadd) {
    winOrigDims = win_dimentions;
    scrFactor = scrFact;
    widePadding = wdPadd;
    soundEngine = irrklang::createIrrKlangDevice();

    mainMenu = new MainMenu(this, soundEngine, win_dimentions, scrFact, wdPadd);
    credits = new Credits(this, win_dimentions, scrFact, wdPadd);
    endlessMode = new EndlessMode(this, soundEngine, winOrigDims, scrFactor, widePadding);
    currentScene = mainMenu;
  }

  ~Game(){
    soundEngine->drop();
    delete endlessMode;
    delete mainMenu;
    delete credits;
  }

  void goToMainMenu(irrklang::ISound *music = NULL, bool AceptCmd = false){
    if (music != NULL)
      mainMenu->setMusic(music);
    mainMenu->isAceptPressed(AceptCmd);
    currentScene = mainMenu;
  }

  void goToEndless(irrklang::ISound *music){
    endlessMode->setMusic(music);
    endlessMode->startGame();
    currentScene = endlessMode;
  }

  void goToCredits(){
    currentScene = credits;
  }

  void execute(GLFWwindow *window){
    currentScene->processInputs(window);
    currentScene->rollCamera();
    currentScene->update();
    currentScene->draw();
  }
};

#endif