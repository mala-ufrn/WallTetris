#ifndef TEXT_RENDER_H
#define TEXT_RENDER_H

#include <glm/glm.hpp>

#include <string>
#include <map>

#include "shader.h"

#define ATLAS_MAXWIDTH 1024

class TextRender {
private:
  // Character Structure
  struct Character {
    glm::vec2  size;       // Size of glyph
    glm::vec2  bearing;    // Offset from baseline to left/top of glyph
    glm::vec2  advance;    // Offset to advance to next glyph
    glm::vec2  texcoord;   // Texture coordinates
  };

  Shader *textShader;

  int charsAtlasWidth,
      charsAtlasHeight,
      iconsAtlasWidth,
      iconsAtlasHeight;

  GLuint txtVBO,
         txtVAO,
         charsTexture,
         iconsTexture;

  std::map<GLchar, Character> charactersAtlas,
                              iconsAtlas;

public:
  TextRender(Shader* textShader, const char* charfontPath, int fontSize);
  TextRender(Shader* textShader, const char* charfontPath, const char* iconfontPath, int fontSize);

  void renderLeft(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 hsvColor);
private:
  void buildTextureAtlas(const char* ttfPath, GLuint* texture, int fontSize,
      std::map<GLchar, Character> *atlas, int* atlasWidth, int* atlasHeight);
};

#endif