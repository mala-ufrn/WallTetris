#include "scenes/credits.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define WIDTH 800.0f
#define HEIGHT 600.0f

Credits::Credits(SceneMaster* sceneMaster, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd){

  this->sceneMaster = sceneMaster;

	winOrigDims = win_dimentions;
	scrFactor = scrFact;
	widePadding = wdPadd;

  textShader = new Shader("res/shaders/text_shader.vs", "res/shaders/text_shader.fs");
  imageShader = new Shader("res/shaders/image_shader.vs", "res/shaders/image_shader.fs");
  glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
  
  textShader->use();
  textShader->setMatrix4f("projection", projection);
  imageShader->use();
  imageShader->setMatrix4f("projection", projection);

  sansPsx64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/IconicPSx.ttf", 64);
  sansKey64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/KeyCapsFLF.ttf", 64);
  
  backGround = new ImageRender(imageShader, "res/img/bkg0.png", 800, 600);
}

Credits::~Credits() {
	delete textShader;
	delete imageShader;
	delete sansPsx64;
	delete sansKey64;
	delete backGround;
}

void Credits::processInputs(GLFWwindow *window) {
	if (glfwJoystickPresent(GLFW_JOYSTICK_2)) {

    jspresent = true;

     int count;
     const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &count);
     if (buttons[1] == GLFW_PRESS) {
       sceneMaster->goToMainMenu();
     }
  }
  else {

    jspresent = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
      sceneMaster->goToMainMenu();
    }
  }
}

void Credits::update() {
}

void Credits::draw() {
  glViewport(*widePadding, 0, winOrigDims.x * *scrFactor, winOrigDims.y * *scrFactor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draws Background
  glDepthRange(0.5f, 1.0f);

  backGround->draw(0.0f, 0.0f, glm::vec3(0.3f));
  
  // draws UI
  glDepthRange(0.0f, 0.5f);

  if (jspresent) {
    sansPsx64->renderLeft("Press \\C to back", 25.0f, 25.0f, 0.35f, glm::vec3(1.0f));
  } else {
    sansKey64->renderLeft("Press \\e to back", 25.0f, 25.0f, 0.35f, glm::vec3(1.0f));
  }
}