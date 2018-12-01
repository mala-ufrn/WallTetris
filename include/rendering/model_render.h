#ifndef MODEL_RENDER_H
#define MODEL_RENDER_H

#include "utils/shader.h"

class ModelRender {
private:

  Shader *quadShader;
  Shader *wireShader;
  Shader *blockShader;
      
  GLuint cubeVBO,
         cubeVAO,

         cbEdgesVBO,
         cbEdgesEBO,
         cbEdgesVAO,
         
         fdWallsVBO,
         fdWallsEBO,
         fdWallsVAO,

         fdEdgesVAO,

         fdBottonVBO,
         fdBottonEBO,
         fdBottonVAO,

         fdCeilingVBO,
         fdCeilingEBO,
         fdCeilingVAO;

  GLfloat cubeVertices[288] = {
  // positions        // normal coords      // texture coords
  // Back face
  0.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, // bottom-right
  1.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, // top-left
  1.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // bottom-left         
  1.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, // top-left
  0.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, // bottom-right
  0.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, // top-right
  // Front face
  0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // bottom-left
  1.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f, // bottom-right
  1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // top-right
  1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // top-right
  0.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, // top-left
  0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // bottom-left
  // Left face
  0.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // top-right
  0.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // top-left
  0.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // bottom-left
  0.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // bottom-left
  0.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // bottom-right
  0.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // top-right
  // Right face
  1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // top-left
  1.0f, 0.0f, 0.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // bottom-right
  1.0f, 1.0f, 0.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // top-right         
  1.0f, 0.0f, 0.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // bottom-right
  1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // top-left
  1.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // bottom-left     
  // Bottom face
  0.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // bottom-left
  1.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // bottom-right
  1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // top-right
  1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // top-right
  0.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // top-left
  0.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // bottom-left
  // Top face
  0.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // top-left
  1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // bottom-right
  1.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f, // top-right     
  1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // bottom-right
  0.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // top-left
  0.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f  // bottom-left        
};

GLfloat cubeEdgesVertices[24] = {
  // positions
  0.0f, 0.0f, 0.0f, // back-bottom-left
  1.0f, 1.0f, 0.0f, // back-top-right
  1.0f, 0.0f, 0.0f, // back-bottom-right
  0.0f, 1.0f, 0.0f, // back-top-left

  0.0f, 0.0f, 1.0f, // front-bottom-left
  1.0f, 0.0f, 1.0f, // front-bottom-right
  1.0f, 1.0f, 1.0f, // front-top-right
  0.0f, 1.0f, 1.0f  // front-top-left
};

GLuint cubeEdgesIndices[24] = {
  0,  2,
  0,  3,
  0,  4,
  1,  2,
  1,  3,
  1,  6,
  5,  2,
  5,  4,
  5,  6,
  7,  3,
  7,  4,
  7,  6
};

GLfloat fieldWallsVertices[56] = {
  // positions           // color
  -0.5f,  0.0f, -0.5f,   0.5f, 0.5f, 0.5f, 0.3f, // back-bottom-left
   0.5f,  1.0f, -0.5f,   0.5f, 0.5f, 0.5f, 0.3f, // back-top-right
   0.5f,  0.0f, -0.5f,   0.5f, 0.5f, 0.5f, 0.3f, // back-bottom-right
  -0.5f,  1.0f, -0.5f,   0.5f, 0.5f, 0.5f, 0.3f, // back-top-left

  -0.5f,  0.0f,  0.5f,   0.5f, 0.5f, 0.5f, 0.3f, // front-bottom-left
   0.5f,  0.0f,  0.5f,   0.5f, 0.5f, 0.5f, 0.3f, // front-bottom-right
   0.5f,  1.0f,  0.5f,   0.5f, 0.5f, 0.5f, 0.3f, // front-top-right
  -0.5f,  1.0f,  0.5f,   0.5f, 0.5f, 0.5f, 0.3f  // front-top-left
};

GLuint fieldWallsIndices[24] = {
  // Back face
  0,  1,  2,
  0,  3,  1,
  // Front face
  4,  5,  6,
  4,  6,  7,
  // Left face
  1,  5,  2,
  1,  6,  5,
  // Right face
  0,  4,  7,
  0,  7,  3
};

GLfloat fieldBottonVertices[28] = {
  // positions           // color
  -0.5f,  0.0f, -0.5f,   0.5f, 0.5f, 0.5f, 0.5f, // back-bottom-left
   0.5f,  0.0f, -0.5f,   0.5f, 0.5f, 0.5f, 0.5f, // back-bottom-right
  -0.5f,  0.0f,  0.5f,   0.5f, 0.5f, 0.5f, 0.5f, // front-bottom-left
   0.5f,  0.0f,  0.5f,   0.5f, 0.5f, 0.5f, 0.5f, // front-bottom-right
};

GLuint fieldBottonIndices[6] = {
  0,  2,  3,
  0,  3,  1
};

GLfloat fieldCeilingVertices[28] = {
  // positions           // color
   0.5f,  0.0f, -0.5f,   1.0f, 0.7f, 0.7f, 0.5f , // back-top-right
  -0.5f,  0.0f, -0.5f,   1.0f, 0.7f, 0.7f, 0.5f , // back-top-left
   0.5f,  0.0f,  0.5f,   1.0f, 0.7f, 0.7f, 0.5f , // front-top-right
  -0.5f,  0.0f,  0.5f,   1.0f, 0.7f, 0.7f, 0.5f   // front-top-left
};

GLuint fieldCeilingIndices[6] = {
  0,  3,  1,
  0,  2,  3
};

public:
  // constructor read vertex and frag files and generates the shader 
  ModelRender(Shader* quadShader, Shader* wireShader, Shader* blockShader);
  ~ModelRender();

  void drawField();
};

#endif