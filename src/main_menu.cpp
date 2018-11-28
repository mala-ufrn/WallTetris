#include "../include/main_menu.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

#define WIDTH 800.0f
#define HEIGHT 600.0f

MainMenu::MainMenu(const glm::vec2 win_dimentions, float* scrFact, float* wdPadd){

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
  soapStore140 = new TextRender(textShader, "res/fonts/soap_store.otf", 140);
  trumpImage = new ImageRender(imageShader, "res/img/main_img.png", 438, 600);
  backGround = new ImageRender(imageShader, "res/img/bkg0.png", 800, 600);
}

MainMenu::~MainMenu() {
	delete textShader;
	delete imageShader;
	delete sansPsx64;
	delete sansKey64;
	delete soapStore140;
	delete trumpImage;
	delete backGround;
}

void MainMenu::processInputs(int* keyCode, int* keyAction) {

}

void MainMenu::update() {
	float hue = (float)((int)(glfwGetTime() * 24) % 360);
  float sat = 1.0;
  float val = 1.0;
  
  int hi = int(hue / 60.0) % 6;
  float f = hue / 60.0 - float(hi);
  float p = val * (1.0 - sat);
  float q = val * (1.0 - sat * f);
  float t = val * (1.0 - sat * (1.0 - f));
  
  if (hi == 0) {
    titleRgb = glm::vec3(val, t, p);
  } else if (hi == 1) {
    titleRgb = glm::vec3(q, val, p);
  } else if (hi == 2) {
    titleRgb = glm::vec3(p, val, t);
  } else if(hi == 3) {
    titleRgb = glm::vec3(p, q, val);
  } else if (hi == 4) {
    titleRgb = glm::vec3(t, p, val);
  } else {
    titleRgb = glm::vec3(val, p, q);
  }

  arrowAnim = sin(glfwGetTime() * 5) * 5;
}

void MainMenu::draw() {
	glViewport(*widePadding, 0, winOrigDims.x * *scrFactor, winOrigDims.y * *scrFactor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  backGround->draw(0.0f, 0.0f, glm::vec3(0.2f, 0.2f, 0.2f));
  trumpImage->draw(362.0f, 0.0f);

  soapStore140->renderLeft("WALLTETRIS", 25.0f, 450.0f, 1.0f, titleRgb);
  sansPsx64->renderLeft("\\!", 40.0f + arrowAnim, 303.0f, 0.6f, glm::vec3(1.0, 1.0, 0.0));
  soapStore140->renderLeft("Endless mode", 85.0f, 300.0f, 0.4f, glm::vec3(0.8, 0.8, 0.0));
  soapStore140->renderLeft("Credits", 85.0f, 240.0f, 0.4f, glm::vec3(0.8, 0.8, 0.8));
  sansKey64->renderLeft("Press \\f to select", 25.0f, 25.0f, 0.35f, glm::vec3(1.0, 1.0, 1.0));
}