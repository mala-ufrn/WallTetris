#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <vector>
 
class Drawable{
public:
  virtual std::vector<std::vector<char>> getShape() = 0;
};

#endif //DRAWABLE_H_