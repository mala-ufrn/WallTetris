#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "scene.h"
#include "shader.h"
#include "text_render.h"
#include "image_render.h"

class MainMenu : public Scene {
private:

  int selected;
  bool pressed;

  float arrowAnim;
  float *scrFactor,
        *widePadding;

  int selected;

  glm::vec2 winOrigDims;
  glm::vec3 titleRgb;

  Shader *textShader,
         *imageShader;
  TextRender *sansPsx64,
             *sansKey64,
             *soapStore140;
  ImageRender *trumpImage,
              *backGround;

public:
  MainMenu(const glm::vec2 win_dimentions, float* scrFact, float* wdPadd);
  ~MainMenu();
  void processInputs(GLFWwindow *window);
  void update();
  void draw();
};
#endif