#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <vector>
using std::vector;

class Drawable{
public:
  virtual vector<vector<char>> getShape() = 0;
};

#endif //DRAWABLE_H_