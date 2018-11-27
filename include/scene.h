#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
  virtual void processInputs() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
};

#endif