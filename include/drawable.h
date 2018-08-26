#ifndef DRAWABLE_H_
#define DRAWABLE_H_

class Drawable{
public:
  virtual unsigned char** getShape() = 0;
  virtual int getWidth() = 0;
  virtual int getHeight() = 0;
};

#endif //DRAWABLE_H_