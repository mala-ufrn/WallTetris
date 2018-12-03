#include "scenes/endless_mode.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>

#define WIDTH 800.0f
#define HEIGHT 600.0f

#define PI 3.14159265

EndlessMode::EndlessMode(SceneMaster* sceneMaster, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd){

  this->sceneMaster = sceneMaster;

  playing = true;
  paused = false;
  highScore = 0;
  score = 0;
  level = 1;
  lines = 0;

  field = new Field(this);
  nextTetr = new Tetromino(field, this);
  activeTetr = NULL;

	winOrigDims = win_dimentions;
	scrFactor = scrFact;
	widePadding = wdPadd;

  textShader = new Shader("res/shaders/text_shader.vs", "res/shaders/text_shader.fs");
  imageShader = new Shader("res/shaders/image_shader.vs", "res/shaders/image_shader.fs");
  quadShader = new Shader("res/shaders/quad_shader.vs", "res/shaders/quad_shader.fs");
  gameWireShader = new Shader("res/shaders/wire_shader.vs", "res/shaders/wire_shader.fs");
  uiWireShader = new Shader("res/shaders/wire_shader.vs", "res/shaders/wire_shader.fs");
  gameBlockShader = new Shader("res/shaders/block_shader.vs", "res/shaders/block_shader.fs");
  uiBlockShader = new Shader("res/shaders/block_shader.vs", "res/shaders/block_shader.fs");

  glm::mat4 orthoProj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
  
  textShader->use();
  textShader->setMatrix4f("projection", orthoProj);
  imageShader->use();
  imageShader->setMatrix4f("projection", orthoProj);

  glm::mat4 perspProj = glm::perspective(glm::radians(45.0f), 0.42f, 0.1f, 80.0f);

  glm::mat4 view = glm::lookAt(glm::vec3(cos(25 * PI / 180.0f) * 30.0f, sin(25 * PI / 180.0f) * 30.0f, 0),
                               glm::vec3(0.0f, 9.0f, 0.0f),
                               glm::vec3(0.0, 1.0, 0.0));

  gameWireShader->use();
  gameWireShader->setMatrix4f("projection", perspProj);
  gameWireShader->setMatrix4f("view", view);

  gameWireShader->use();
  gameWireShader->setMatrix4f("projection", perspProj);
  gameWireShader->setMatrix4f("view", view);

  gameBlockShader->use();
  gameBlockShader->setMatrix4f("projection", perspProj);
  gameBlockShader->setMatrix4f("view", view);

  quadShader->use();
  quadShader->setMatrix4f("projection", perspProj);
  quadShader->setMatrix4f("view", view);

  glm::vec3 camPos = glm::vec3(0.0f, sin(15 * PI / 180.0f) * 8.0f, cos(15 * PI / 180.0f) * 8.0f);

  perspProj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 80.0f);

  view = glm::lookAt(camPos,
                     glm::vec3(0.0f),
                     glm::vec3(0.0, 1.0, 0.0));

  uiWireShader->use();
  uiWireShader->setMatrix4f("projection", perspProj);
  uiWireShader->setMatrix4f("view", view);

  uiBlockShader->use();
  uiBlockShader->setMatrix4f("projection", perspProj);
  uiBlockShader->setMatrix4f("view", view);
  uiBlockShader->setVector3f("viewPos", camPos);
  uiBlockShader->setVector3f("lightPos", 0.0f, 10.0f, 20.0f);
  uiBlockShader->setVector3f("lightColor", glm::vec3(1.0f));

  sansPsx64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/IconicPSx.ttf", 64);
  sansKey64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/KeyCapsFLF.ttf", 64);
  
  backGround = new ImageRender(imageShader, "res/img/bkg0.png", 800, 600);
  fieldBGround = new ImageRender(imageShader, "res/img/bkg1.png", 250, 550);
  nextBGround = new ImageRender(imageShader, "res/img/bkg2.png", 120, 120);

  gameModelRender = new ModelRender(quadShader, gameWireShader, gameBlockShader);
  uiModelRender = new ModelRender(quadShader, uiWireShader, uiBlockShader);
}

EndlessMode::~EndlessMode() {

	delete sansPsx64;
  delete sansKey64;
	delete backGround;
  delete fieldBGround;
  delete nextBGround;
  delete gameModelRender;
  delete uiModelRender;

  delete textShader;
  delete imageShader;
  delete quadShader;
  delete gameWireShader;
  delete uiWireShader;
  delete gameBlockShader;
  delete uiBlockShader;
}

void EndlessMode::createNextTetr(int posX){
  activeTetr = nextTetr;
  nextTetr = new Tetromino(field, this);
}

void EndlessMode::increaseScore(int value){
  
  score += value;

  if (highScore < score) {
    highScore = score;
  }
}

void EndlessMode::increaseLines(int quantity){ 

  lines += quantity;

  if (lines > 1 && lines <= 90) {
    level = 1 + (lines-1)/10;
  }
  else {
    level = 10;
  }
}

void EndlessMode::gameOver() {

}

void EndlessMode::processInputs(GLFWwindow *window) {

  if (glfwJoystickPresent(GLFW_JOYSTICK_2)) {
    jspresent = true;

  } else {
    jspresent = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
      sceneMaster->goToMainMenu();
    }
  }
}

void EndlessMode::update() {
  
}

void EndlessMode::draw() {

  glViewport(*widePadding, 0, winOrigDims.x * *scrFactor, winOrigDims.y * *scrFactor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draws Background
  glDepthRange(0.95f, 1.0f);
  backGround->draw(0.0f, 0.0f, glm::vec3(0.3f));
  fieldBGround->draw(120.0f, 25.0f, glm::vec3(0.05f));
  nextBGround->draw(447.5f, 297.5, glm::vec3(0.05f));

  // draws Models
  glDepthRange(0.05f, 0.95f);
  glViewport(*widePadding + (145 * *scrFactor), 0, 300 * *scrFactor, winOrigDims.y * *scrFactor);
  gameModelRender->drawField();

  // draws UI
  glDepthRange(0.0f, 0.05f);
  glViewport(*widePadding + (520 * *scrFactor), 330 * *scrFactor, 180 * *scrFactor, 180 * *scrFactor);
  uiModelRender->drawNext(nextTetr->getShape());

  glViewport(*widePadding, 0, winOrigDims.x * *scrFactor, winOrigDims.y * *scrFactor);

  sansKey64->renderLeft("High score: " + std::to_string(highScore), 430.0f, 510.0f, 0.35f, glm::vec3(8.0f, 0.7f, 0.3f));
  sansKey64->renderLeft("Player score: " + std::to_string(score), 430.f, 475.0f, 0.4f, glm::vec3(0.8f));
  sansKey64->renderLeft("Level: " + std::to_string(level), 430.f, 445.0f, 0.35f, glm::vec3(0.8f));
  sansKey64->renderLeft("Next:", 460.f, 390.0f, 0.35f, glm::vec3(0.8f));

  sansKey64->renderLeft("Commands:", 430.f, 240.0f, 0.30f, glm::vec3(0.6f));

  if (jspresent) {
    sansPsx64->renderLeft("\\E: move left/reight", 430.0f, 210.0f, 0.35f, glm::vec3(0.6f));
    sansPsx64->renderLeft("\\C: roll", 430.0f, 180.0f, 0.35f, glm::vec3(0.6f));
    sansPsx64->renderLeft("\\G: speed up", 430.0f, 150.0f, 0.35f, glm::vec3(0.6f));
    sansPsx64->renderLeft("\\A: pause", 430.0f, 120.0f, 0.35f, glm::vec3(0.6f));
  } else {
    sansKey64->renderLeft("\\A or \\a: move left", 430.0f, 210.0f, 0.35f, glm::vec3(0.6f));
    sansKey64->renderLeft("\\D or \\d: move right", 430.0f, 180.0f, 0.35f, glm::vec3(0.6f));
    sansKey64->renderLeft("\\W or \\w: roll", 430.0f, 150.0f, 0.35f, glm::vec3(0.6f));
    sansKey64->renderLeft("\\S or \\s: speed up", 430.0f, 120.0f, 0.35f, glm::vec3(0.6f));
    sansKey64->renderLeft("\\P or \\e: pause", 430.0f, 90.0f, 0.35f, glm::vec3(0.6f));
  }
}