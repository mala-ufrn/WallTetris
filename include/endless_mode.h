#ifndef ENDLESS_MODE_H
#define ENDLESS_MODE_H

#include <glm/glm.hpp>

#include "scene.h"
#include "scene_master.h"
#include "shader.h"
#include "text_render.h"
#include "image_render.h"

class EndlessMode : public Scene {
private:

  SceneMaster *sceneMaster;

  float *scrFactor,
        *widePadding;

  glm::vec2 winOrigDims;

  Shader *textShader,
         *imageShader;
  TextRender *sansPsx64,
             *sansKey64;
  ImageRender *backGround;

public:
  EndlessMode(SceneMaster* sceneMaster, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd);
  ~EndlessMode();
  void processInputs(GLFWwindow *window);
  void update();
  void draw();
};
#endif