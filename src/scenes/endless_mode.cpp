#include "scenes/endless_mode.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>

#define WIDTH 800.0f
#define HEIGHT 600.0f

#define PI 3.14159265

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
  quadShader = new Shader("res/shaders/quad_shader.vs", "res/shaders/quad_shader.fs");
  wireShader = new Shader("res/shaders/wire_shader.vs", "res/shaders/wire_shader.fs");
  blockShader = new Shader("res/shaders/block_shader.vs", "res/shaders/block_shader.fs");

  glm::mat4 orthoProj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
  
  textShader->use();
  textShader->setMatrix4f("projection", orthoProj);
  imageShader->use();
  imageShader->setMatrix4f("projection", orthoProj);

  sansPsx64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/IconicPSx.ttf", 64);
  sansKey64 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/KeyCapsFLF.ttf", 64);
  
  backGround = new ImageRender(imageShader, "res/img/bkg0.png", 800, 600);

  modelRender = new ModelRender(quadShader, wireShader, blockShader);

  glm::mat4 perspProj = glm::perspective(glm::radians(45.0f), 0.45f, 0.1f, 80.0f);

  glm::mat4 view = glm::lookAt(glm::vec3(cos(30 * PI / 180.0f) * 30.0f, 0.5f * 30.0f, 0),
                               glm::vec3(0.0f, 9.0f, 0.0f),
                               glm::vec3(0.0, 1.0, 0.0));

  wireShader->use();
  wireShader->setMatrix4f("projection", perspProj);
  wireShader->setMatrix4f("view", view);

  quadShader->use();
  quadShader->setMatrix4f("projection", perspProj);
  quadShader->setMatrix4f("view", view);
}

EndlessMode::~EndlessMode() {
	delete textShader;
	delete imageShader;
	delete sansPsx64;
  delete sansKey64;
	delete backGround;
  delete quadShader;
  delete wireShader;
  delete blockShader;
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
  
}

void EndlessMode::draw() {
  glViewport(*widePadding, 0, winOrigDims.x * *scrFactor, winOrigDims.y * *scrFactor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  backGround->draw(0.0f, 0.0f, glm::vec3(0.3f, 0.3f, 0.3f));
  sansKey64->renderLeft("Press \\Q to back", 25.0f, 25.0f, 0.35f, glm::vec3(1.0, 1.0, 1.0));

  glViewport(*widePadding + (150 * *scrFactor), 0, 300 * *scrFactor, winOrigDims.y * *scrFactor);
  modelRender->drawField();
}