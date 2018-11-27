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

float enlargeFactor = 1.0f,
      widePadding = 0.0f;

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

  TextRender* freeSans48 = new TextRender(textShader, "res/fonts/FreeSans.ttf", "res/fonts/IconicPSx.ttf", 48);
  TextRender* soapStore140 = new TextRender(textShader, "res/fonts/soap_store.otf", 140);
  ImageRender* trumpImage = new ImageRender(imageShader, "res/img/main_bg1.png", 438, 600);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

    
  while (!glfwWindowShouldClose(window)) {
    // Process inputs

    // Update the game

    // Render
    glViewport(widePadding, 0, WIDTH * enlargeFactor, HEIGHT * enlargeFactor);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float hue = (float)((int)(glfwGetTime() * 24) % 360);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    trumpImage->draw(362.0f, 0.0f);
    freeSans48->renderLeft("Press \\X to select", 25.0f, 25.0f, 0.5f, glm::vec3(0.0, 0.0, 1.0));
    soapStore140->renderLeft("WALLTETRIS", 25.0f, 450.0f, 1.0f, glm::vec3(hue, 1.0, 1.0));

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
  enlargeFactor = height/HEIGHT;
  if (float(width)/height != 4.0f/3.0f){
    widePadding = (width - WIDTH * enlargeFactor) / 2.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_SCISSOR_TEST);
    glScissor(widePadding, 0, WIDTH * enlargeFactor,HEIGHT * enlargeFactor);
  } else {
    glDisable(GL_SCISSOR_TEST);
    widePadding = 0.0f;
  }
}