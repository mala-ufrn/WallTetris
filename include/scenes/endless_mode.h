#ifndef ENDLESS_MODE_H
#define ENDLESS_MODE_H

#include <glm/glm.hpp>

#include "scene.h"
#include "scene_master.h"
#include "utils/shader.h"
#include "rendering/text_render.h"
#include "rendering/image_render.h"
#include "models/tetromino.h"
#include "models/field.h"

class EndlessMode : public Scene, public GameMaster {
private:

  SceneMaster *sceneMaster;

  // Flag for new game
  bool playing;
  // Flag for pause
  bool paused;
  // Player score
  int score;
  // Game level
  int level;
  // Lines counter (Def. Level)
  int lines;

  float *scrFactor,
        *widePadding;

  glm::vec2 winOrigDims;

  //Game field
  Field* field;
  //Next tetromino
  Tetromino* nextTetr;
  //Active tetromino
  Tetromino* activeTetr;
  //Object that draws the game scene

  Shader *textShader,
         *imageShader;
  TextRender *sansPsx64,
             *sansKey64;
  ImageRender *backGround;

public:
  EndlessMode(SceneMaster* sceneMaster, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd);
  ~EndlessMode();
  void createNextTetr(int posX);
  void increaseScore(int value){ score += value; }
  void increaseLines(int quantity);
  void processInputs(GLFWwindow *window);
  void update();
  void draw();
};
#endif