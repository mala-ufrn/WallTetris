#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
  virtual void processInputs(int* keyCode, int* keyAction) = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
};

#endif