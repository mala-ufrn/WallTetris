#ifndef Credits_H
#define Credits_H

#include <glm/glm.hpp>

#include "scene.h"
#include "scene_master.h"
#include "shader.h"
#include "text_render.h"
#include "image_render.h"

class Credits : public Scene {
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
  Credits(SceneMaster* sceneMaster, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd);
  ~Credits();
  void processInputs(GLFWwindow *window);
  void update();
  void draw();
};
#endif