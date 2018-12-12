#include "scenes/main_menu.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

#define WIDTH 800.0f
#define HEIGHT 600.0f

MainMenu::MainMenu(SceneMaster* sceneMaster, irrklang::ISoundEngine* soundEngine, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd){

  this->sceneMaster = sceneMaster;

	winOrigDims = win_dimentions;
	scrFactor = scrFact;
	widePadding = wdPadd;
  selected = 0;
  pressed = false;
  jspresent = false;
  aceptPressed = false;
  this->soundEngine = soundEngine;
  music = soundEngine->play2D("res/music/korobeiniki_remix_v0.ogg", true, false, true);
  music->setVolume(0.1f);

	textShader = new Shader("res/shaders/text_shader.vs", "res/shaders/text_shader.fs");
  imageShader = new Shader("res/shaders/image_shader.vs", "res/shaders/image_shader.fs");

  glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
  
  textShader->use();
  textShader->setMatrix4f("projection", projection);
  imageShader->use();
  imageShader->setMatrix4f("projection", projection);

  trumpImage = new ImageRender(imageShader, "res/img/main_img.png", 438, 600);
  backGround = new ImageRender(imageShader, "res/img/bkg0.png", 800, 600);

  sansPsx64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/IconicPSx.ttf", 64);
  sansKey64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/KeyCapsFLF.ttf", 64);
  soapStore200 = new TextRender(textShader, "res/fonts/soap_store.otf", 200);
}

MainMenu::~MainMenu() {
	delete textShader;
	delete imageShader;
	delete sansPsx64;
	delete sansKey64;
	delete soapStore200;
	delete trumpImage;
	delete backGround;
}

void MainMenu::processInputs(GLFWwindow *window) {
  bool mDownCmd;
  bool mUpCmd;
  bool aceptCmd;

	if (glfwJoystickPresent(GLFW_JOYSTICK_2)) {
    jspresent = true;

    // Capture axis and buttons
    int numAxis;
		const float *axis = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &numAxis);
    int numButtons;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &numButtons);
		
    mDownCmd = axis[7] == 1 || axis[1] > 0.3f;
    mUpCmd = axis[7] == -1 || axis[1] < -0.3f;
    aceptCmd = buttons[0] == GLFW_PRESS;
	
  } else {
    jspresent = false;

    mDownCmd = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
    mUpCmd = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    aceptCmd = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
  }

  if (mDownCmd || mUpCmd) {
    if (!pressed){
      selected = (selected + 1) % 2;
      soundEngine->play2D("res/sounds/bleep.ogg", false);
    }
    pressed = true;
  } else {
    pressed = false;
  }

  if (aceptCmd){
    if (!aceptPressed) {
      if (selected == 0){
        unsigned int musicPos = music->getPlayPosition();
        music->stop();
        music->drop();
        music = soundEngine->play2D("res/music/korobeiniki_remix_v1.ogg", true, false, true);
        music->setPlayPosition(musicPos);
        music->setVolume(0.09f);
        sceneMaster->goToEndless(music);
      } else {
        sceneMaster->goToCredits();
      }
      soundEngine->play2D("res/sounds/powerup.wav", false);
    }
  } else {
    aceptPressed = false;
  }
}

void MainMenu::update() {
  float hue = (float)((int)(glfwGetTime() * 24) % 360);
  float sat = 1.0f;
  float val = 1.0f;
  
  int hi = int(hue / 60.0f) % 6;
  float f = hue / 60.0f - float(hi);
  float p = val * (1.0f - sat);
  float q = val * (1.0f - sat * f);
  float t = val * (1.0f - sat * (1.0f - f));
  
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

void MainMenu::rollCamera() {
}

void MainMenu::draw() {
  glViewport(*widePadding, 0, winOrigDims.x * *scrFactor, winOrigDims.y * *scrFactor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draws Background
  glDepthRange(0.5f, 1.0f);

  backGround->draw(0.0f, 0.0f, glm::vec3(0.3f));
  trumpImage->draw(362.0f, 0.0f);

  // draws UI
  glDepthRange(0.0f, 0.5f);

  glm::vec3 white(0.8f, 0.8f, 0.8f);
  glm::vec3 yellow(0.8f, 0.8f, 0.0f);
  soapStore200->renderLeft("WALLTETRIS", 25.0f, 450.0f, 0.7f, titleRgb);
  sansPsx64->renderLeft("\\!", 40.0f + arrowAnim, 303.0f - selected*60, 0.6f, glm::vec3(1.0f, 1.0f, 0.0f));
  soapStore200->renderLeft("Endless mode", 85.0f, 300.0f, 0.28f, !selected? yellow : white);
  soapStore200->renderLeft("Credits", 85.0f, 240.0f, 0.28f, selected? yellow : white);
  if (jspresent) {
    sansPsx64->renderLeft("Press \\X to select", 25.0f, 25.0f, 0.35f, glm::vec3(1.0f));
  } else {
    sansKey64->renderLeft("Press \\f to select", 25.0f, 25.0f, 0.35f, glm::vec3(1.0f));
  }
}