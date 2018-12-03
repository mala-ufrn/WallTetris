#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Scene {
public:
  virtual void processInputs(GLFWwindow *window) = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void rollCamera() = 0;
};

#endif