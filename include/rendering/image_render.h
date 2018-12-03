#ifndef IMAGE_RENDER_H
#define IMAGE_RENDER_H

#include "utils/shader.h"

class ImageRender {
private:

  Shader *imageShader;
      
  GLuint VBO,
         VAO,
         EBO,
         texture;

  GLfloat vertices[16] = {
    // positions  // texture coords
    0.0f, 0.0f,   1.0f, 1.0f,   // top right
    0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
    0.0f, 0.0f,   0.0f, 1.0f    // top left 
  };

  GLuint indices[6] = {  
    0, 3, 1, // first triangle
    1, 3, 2  // second triangle
  };

public:
  // constructor read vertex and frag files and generates the shader 
  ImageRender(Shader* imageShader, const char* imagePath, GLfloat width, GLfloat heigth);
  ~ImageRender();

  void draw(GLfloat x, GLfloat y, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
};

#endif