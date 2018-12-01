#include "rendering/model_render.h"

#include <glm/gtc/matrix_transform.hpp>

#include "utils/stb_image.h"

#include <fstream>
#include <sstream>
#include <iostream>


ModelRender::ModelRender(Shader* quadShader, Shader* wireShader, Shader* blockShader){
  
  this->quadShader = quadShader;
  this->wireShader = wireShader;
  this->blockShader = blockShader;

  GLuint texture;

  stbi_set_flip_vertically_on_load(true);
  // generating texture 1
  glGenTextures(1, &texture);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  // load and generate the texture
  int txWidth,
      txHeight,
      txChannels;
  unsigned char *data = stbi_load("res/img/bkg0.png", &txWidth, &txHeight, &txChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, txWidth, txHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load container texture" << std::endl;
  }
  // free file memory
  stbi_image_free(data);

  // Vertex Buffers and Arrays Creation

  glGenBuffers(1, &cubeVBO);
  glGenVertexArrays(1, &cubeVAO);

  glGenBuffers(1, &cbEdgesVBO);
  glGenBuffers(1, &cbEdgesEBO);
  glGenVertexArrays(1, &cbEdgesVAO);
  
  glGenBuffers(1, &fdWallsVBO);
  glGenBuffers(1, &fdWallsEBO);
  glGenVertexArrays(1, &fdWallsVAO);

  glGenVertexArrays(1, &fdEdgesVAO);

  glGenBuffers(1, &fdBottonVBO);
  glGenBuffers(1, &fdBottonEBO);
  glGenVertexArrays(1, &fdBottonVAO);

  glGenBuffers(1, &fdCeilingVBO);
  glGenBuffers(1, &fdCeilingEBO);
  glGenVertexArrays(1, &fdCeilingVAO);

  // Binding and configuring

  // Cubes
  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  // Cubes edges
  glBindVertexArray(cbEdgesVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cbEdgesEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeEdgesIndices), cubeEdgesIndices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, cbEdgesVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeEdgesVertices), cubeEdgesVertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  // Field walls
  glBindVertexArray(fdWallsVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fdWallsEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fieldWallsIndices), fieldWallsIndices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, fdWallsVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fieldWallsVertices), fieldWallsVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  // Field edges
  glBindVertexArray(fdEdgesVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cbEdgesEBO);
  glBindBuffer(GL_ARRAY_BUFFER, fdWallsVBO);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  // Field botton
  glBindVertexArray(fdBottonVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fdBottonEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fieldBottonIndices), fieldBottonIndices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, fdBottonVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fieldBottonVertices), fieldBottonVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  // Field ceiling
  glBindVertexArray(fdCeilingVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fdCeilingEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fieldCeilingIndices), fieldCeilingIndices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, fdCeilingVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fieldCeilingVertices), fieldCeilingVertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
}

ModelRender::~ModelRender(){
  glDeleteBuffers(1, &cubeVBO);
  glDeleteVertexArrays(1, &cubeVAO);

  glDeleteBuffers(1, &cbEdgesVBO);
  glDeleteBuffers(1, &cbEdgesEBO);
  glDeleteVertexArrays(1, &cbEdgesVAO);
  
  glDeleteBuffers(1, &fdWallsVBO);
  glDeleteBuffers(1, &fdWallsEBO);
  glDeleteVertexArrays(1, &fdWallsVAO);

  glDeleteVertexArrays(1, &fdEdgesVAO);

  glDeleteBuffers(1, &fdBottonVBO);
  glDeleteBuffers(1, &fdBottonEBO);
  glDeleteVertexArrays(1, &fdBottonVAO);

  glDeleteBuffers(1, &fdCeilingVBO);
  glDeleteBuffers(1, &fdCeilingEBO);
  glDeleteVertexArrays(1, &fdCeilingVAO);
}

void ModelRender::drawField(){
  // translate the model
  glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 18.0f, 4.0f));
  
  wireShader->use();
  wireShader->setMatrix4f("model", model);
  wireShader->setVector4f("wireColor", 0.8f, 0.8f, 0.8f, 0.3f);

  glBindVertexArray(fdEdgesVAO);
  glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);

  model = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 18.0f, 2.0f));

  quadShader->use();
  quadShader->setMatrix4f("model", model);

  glBindVertexArray(fdWallsVAO);
  glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
}