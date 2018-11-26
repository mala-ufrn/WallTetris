// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <ctime>
#include <iostream>

#include "../include/shader.h"
#include "../include/text_render.h"
#include "../include/image_render.h"

const GLfloat WIDTH = 960,
             HEIGHT = 720;

float widthFactor = 1.0f,
      heightFactor = 1.0f;

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
  //Game*game = new Game(new GlutDrawer());

  // TESTE << EXCLUIR>> ///////////////////////////////////////////////////////////////////////////////////////////
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Shader* textShader = new Shader("res/shaders/text_shader.vs", "res/shaders/text_shader.fs");
  Shader* imageShader = new Shader("res/shaders/image_shader.vs", "res/shaders/image_shader.fs");

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
  textShader->use();
  textShader->setMatrix4f("projection", projection);

  imageShader->use();
  imageShader->setMatrix4f("projection", projection);

  TextRender* textRender48 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/IconicPSx2.ttf", 48);
  ImageRender* trumpImage = new ImageRender(imageShader, "res/img/main_bg1.png", 73, 100);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    
  while (!glfwWindowShouldClose(window)) {
    // Process inputs

    // Update the game

    // Render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, WIDTH * widthFactor, HEIGHT * heightFactor);

    trumpImage->draw(0.0f, 0.0f);
    textRender48->renderLeft("Press \\X to select", 25.0f, 25.0f, 0.5f, glm::vec3(1.0, 1.0, 1.0));

    glfwSwapBuffers(window);
    glfwPollEvents();

    //glfwSetWindowShouldClose(window, GLFW_TRUE);
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
  widthFactor = width/WIDTH;
  heightFactor = height/HEIGHT;
}