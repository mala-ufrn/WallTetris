#include "scenes/endless_mode.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define WIDTH 800.0f
#define HEIGHT 600.0f

EndlessMode::EndlessMode(SceneMaster* sceneMaster, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd){

  this->sceneMaster = sceneMaster;

  field = NULL;
  nextTetr = NULL;
  activeTetr = NULL;

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

EndlessMode::~EndlessMode() {
	delete textShader;
	delete imageShader;
	delete sansPsx64;
  delete sansKey64;
	delete backGround;
}

void EndlessMode::createNextTetr(int posX) {

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

void EndlessMode::processInputs(GLFWwindow *window) {
// 	if (glfwJoystickPresent(GLFW_JOYSTICK_2)) {
// 		int numAxis;
// 		const float *axis = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &numAxis);

// /*  for (int i = 0; i < numAxis; i++) {
// 			std::cout << axis[i] << " ";
// 		}
// 		std::cout << std::endl;
// */
// 		if (axis[7] != 0 || axis[1] < -0.3f || axis[1] > 0.3f) {
// 	    if (!pressed){
// 	      selected = (selected + 1) % 2;
// 	    }
// 	    pressed = true;
//   	}  else if (pressed){
//     	pressed = false;
//   	}
// 	}
	
//   else {
//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//       if (!pressed){
//         selected = (selected + 1) % 2;
//       }
//       pressed = true;
//     }  else if (pressed){
//       pressed = false;
//     }

  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    sceneMaster->goToMainMenu();
  }
}

void EndlessMode::update() {
  // float hue = (float)((int)(glfwGetTime() * 24) % 360);
  // float sat = 1.0;
  // float val = 1.0;
  
  // int hi = int(hue / 60.0) % 6;
  // float f = hue / 60.0 - float(hi);
  // float p = val * (1.0 - sat);
  // float q = val * (1.0 - sat * f);
  // float t = val * (1.0 - sat * (1.0 - f));
  
  // if (hi == 0) {
  //   titleRgb = glm::vec3(val, t, p);
  // } else if (hi == 1) {
  //   titleRgb = glm::vec3(q, val, p);
  // } else if (hi == 2) {
  //   titleRgb = glm::vec3(p, val, t);
  // } else if(hi == 3) {
  //   titleRgb = glm::vec3(p, q, val);
  // } else if (hi == 4) {
  //   titleRgb = glm::vec3(t, p, val);
  // } else {
  //   titleRgb = glm::vec3(val, p, q);
  // }

  // arrowAnim = sin(glfwGetTime() * 5) * 5;
}

void EndlessMode::draw() {
  glViewport(*widePadding, 0, winOrigDims.x * *scrFactor, winOrigDims.y * *scrFactor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  backGround->draw(0.0f, 0.0f, glm::vec3(0.3f, 0.3f, 0.3f));
  sansKey64->renderLeft("Press \\Q to back", 25.0f, 25.0f, 0.35f, glm::vec3(1.0, 1.0, 1.0));
}