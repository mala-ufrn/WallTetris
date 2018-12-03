#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <glm/glm.hpp>

#include "scene.h"
#include "scene_master.h"
#include "utils/shader.h"
#include "rendering/text_render.h"
#include "rendering/image_render.h"

class MainMenu : public Scene {
private:

  SceneMaster *sceneMaster;

  int selected;
  bool pressed;
  bool jspresent;

  float arrowAnim;
  float *scrFactor,
        *widePadding;

  glm::vec2 winOrigDims;
  glm::vec3 titleRgb;

  Shader *textShader,
         *imageShader;
  TextRender *sansPsx64,
             *sansKey64,
             *soapStore200;
  ImageRender *trumpImage,
              *backGround;

public:
  MainMenu(SceneMaster* sceneMaster, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd);
  ~MainMenu();
  void processInputs(GLFWwindow *window);
  void update();
  void draw();
};
#endif