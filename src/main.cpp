// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>

#include <iostream>

#include "game.h"

const glm::vec2 WIN_ORIG_DIM = glm::vec2(960.0f, 720.0f);

float scrFactor = 1.0f,
      widePadding = 0.0f;

const GLchar *WINDOW_TITLE = "WALLTETRIS";

//Func prototipes
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char *argv[]) {

  // Initialize GLFW lib
  if (!glfwInit()) {
    std::cout << "Failed to init GLFW" << std::endl;
    return -1;
  }

  // Create a windowed mode window and its OpenGL context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIN_ORIG_DIM.x, WIN_ORIG_DIM.y, WINDOW_TITLE, NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glfwSetWindowAspectRatio(window, 4, 3);

  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Set  callback functions
  glfwSetErrorCallback(errorCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Create game's objects
  Game *game = new Game(WIN_ORIG_DIM, &scrFactor, &widePadding);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  
  glfwSetTime(0.0000);  
  while (!glfwWindowShouldClose(window)) {
    game->execute(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // terminate game's objects
  delete game;

  glfwTerminate();
  return 0;
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  scrFactor = height/WIN_ORIG_DIM.y;

  if (float(width)/height != 4.0f/3.0f){
    widePadding = (width - WIN_ORIG_DIM.x * scrFactor) / 2.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
    glScissor(widePadding, 0, WIN_ORIG_DIM.x * scrFactor, WIN_ORIG_DIM.y * scrFactor);
  } else {
    glDisable(GL_SCISSOR_TEST);
    widePadding = 0.0f;
  }
}