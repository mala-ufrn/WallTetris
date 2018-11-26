// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>

#include <ctime>
#include <iostream>

//#include "../include/game.h"
//#include "../include/glut_drawer.h"

const GLuint WIDTH = 1280,
             HEIGHT = 720;

const GLchar *WINDOW_TITLE = "WALLTETRIS";

//Func prototipes
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(int argc, char *argv[]) {

  // Generate srand seed
  srand(time(NULL));

  // Initialize GLFW lib
  if (!glfwInit()) {
    std::cout << "Failed to init GLFW" << std::endl;
    return -1;
  }

  // Create a windowed mode window and its OpenGL context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glfwSetWindowAspectRatio(window, 16, 9);

  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Set  callback functions
  glfwSetErrorCallback(errorCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Create game's objects
  //Game*game = new Game(new GlutDrawer());
    
  while (!glfwWindowShouldClose(window)) {
    // Process inputs

    // Update the game

    // Render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // terminate game's objects
  // delete game;

  glfwTerminate();
  return 0;
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}