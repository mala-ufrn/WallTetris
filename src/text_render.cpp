#include "../include/text_render.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

TextRender::TextRender(Shader* textShader, const char* charfontPath, int fontSize){
  this->textShader = textShader;

  buildTextureAtlas(charfontPath, &charsTexture, fontSize, &charactersAtlas, &charsAtlasWidth, &charsAtlasHeight);

  glGenBuffers(1, &txtVBO);
  glGenVertexArrays(1, &txtVAO);

  glBindVertexArray(txtVAO);
  glBindBuffer(GL_ARRAY_BUFFER, txtVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
}

TextRender::TextRender(Shader* textShader, const char* charfontPath, const char* iconfontPath, int fontSize){
  this->textShader = textShader;

  buildTextureAtlas(charfontPath, &charsTexture, fontSize, &charactersAtlas, &charsAtlasWidth, &charsAtlasHeight);
  buildTextureAtlas(iconfontPath, &iconsTexture, fontSize, &iconsAtlas, &iconsAtlasWidth, &iconsAtlasHeight);

  glGenBuffers(1, &txtVBO);
  glGenVertexArrays(1, &txtVAO);

  glBindVertexArray(txtVAO);
  glBindBuffer(GL_ARRAY_BUFFER, txtVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
}

void TextRender::renderLeft(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color){
  // Activate corresponding render state  
  textShader->use();
  textShader->setVector3f("textColor", color);
  glBindVertexArray(txtVAO);
  // Activate corresponding texture
  glActiveTexture(GL_TEXTURE0);

  GLuint *texture = &charsTexture;
  int *atlasWidth = &charsAtlasWidth,
      *atlasHeight = &charsAtlasHeight;

  bool isIcon = false;
  // Iterate through all characters
  std::string::const_iterator c;

  for (c = text.begin(); c != text.end(); c++){

    if (*c == '\\' && iconsAtlas.size() != 0){
      isIcon = true;
      texture = &iconsTexture;
      atlasWidth = &iconsAtlasWidth;
      atlasHeight = &iconsAtlasHeight;
      continue;
    }

    Character ch;
    if (isIcon) {
      ch = iconsAtlas[*c];
    } else {
      ch = charactersAtlas[*c];
    }

    GLfloat xpos = x + ch.bearing.x * scale;
    GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

    GLfloat w = ch.size.x * scale;
    GLfloat h = ch.size.y * scale;
    
    // Update VBO for each character
    GLfloat vertices[6][4] = {
      // positions            // texture coords 
      { xpos,     ypos + h,   ch.texcoord.x,                           ch.texcoord.y},            
      { xpos,     ypos,       ch.texcoord.x,                           ch.texcoord.y +ch.size.y / *atlasHeight},
      { xpos + w, ypos,       ch.texcoord.x + ch.size.x / *atlasWidth, ch.texcoord.y+ ch.size.y / *atlasHeight},

      { xpos,     ypos + h,   ch.texcoord.x,                           ch.texcoord.y},
      { xpos + w, ypos,       ch.texcoord.x + ch.size.x / *atlasWidth, ch.texcoord.y + ch.size.y / *atlasHeight},
      { xpos + w, ypos + h,   ch.texcoord.x + ch.size.x / *atlasWidth, ch.texcoord.y}
    };

    // bind texture
    glBindTexture(GL_TEXTURE_2D, *texture);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, txtVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.advance.x) * scale;

    if (isIcon) {
      texture = &charsTexture;
      atlasWidth = &charsAtlasWidth,
      atlasHeight = &charsAtlasHeight;
      isIcon = false;
    }
  }
}

void TextRender::buildTextureAtlas(const char* ttfPath, GLuint* texture, int fontSize,
                       std::map<GLchar, Character> *atlas, int* atlasWidth, int* atlasHeight){
  // Load Fonts
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

  FT_Face face;

  if(FT_New_Face(ft, ttfPath, 0, &face))
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl; 

  FT_Set_Pixel_Sizes(face, 0, fontSize);

  // Get texture atlas width and height
  FT_GlyphSlot g = face->glyph;
  unsigned int width,
               height,
               roww,
               rowh;

  width = height = roww = rowh = 0;

  for(int i = 32; i < 128; i++) {
    if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }

    if(roww + g->bitmap.width + 1 >= ATLAS_MAXWIDTH) {
      width = std::max(width, roww);
      height += rowh + 1;
      roww = 0;
      rowh = 0;
    }
    roww += g->bitmap.width + 1;
    rowh = std::max(rowh, g->bitmap.rows);
  }

  width = std::max(width, roww);
  height += rowh;

  *atlasWidth = width;
  *atlasHeight = height;

  // Create New Texture
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

  std::vector<GLubyte> emptyData(width * height, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, &emptyData[0]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int offsetX = 0,
      offsetY = 0;

  rowh = 0;

  for(GLubyte c = 32; c < 128; c++) {
    // Load character glyph 
    if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }

    if (offsetX + g->bitmap.width + 1 >= ATLAS_MAXWIDTH) {
      offsetY += rowh + 1;
      rowh = 0;
      offsetX = 0;
    }

    // append texture atlas
    glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
    
    Character character = {
      glm::vec2(g->bitmap.width, g->bitmap.rows),
      glm::vec2(g->bitmap_left, g->bitmap_top),
      glm::vec2(g->advance.x >> 6, g->advance.y >> 6),
      glm::vec2((float)offsetX / *atlasWidth, (float)offsetY / *atlasHeight)
    };
    atlas->insert(std::pair<GLchar, Character>(c, character));

    rowh = std::max(rowh, g->bitmap.rows);
    offsetX += g->bitmap.width + 1;
  }

  glGenerateMipmap(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Restore byte-aligment restriction

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}