#include "../include/glut_drawer.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#define START_X 4
#define START_Y 0

#define PI 3.14159265
#define DISTANCE 22

//Colors to printer output
enum Color {
  CLEAR = 0,
  BLACK = 30,
  RED = 114,
  GREEN = 103,
  YELLOW = 121,
  NAIVE_BLUE = 110,
  ORANGE = 111,
  PURPLE = 112,
  BLUE = 98,
  WHITE = 119
};

GlutDrawer* GlutDrawer::drawer;

GlutDrawer::GlutDrawer() {
  lastX = lastY = 0;
  lastShape = NULL;
  lastPiece = NULL;
}


void GlutDrawer::init(string player, Drawable* field) {
  drawer = this;
  glClearColor(0.3, 0.3, 0.3, 0.0);

  glMatrixMode(GL_PROJECTION);
  //glFrustum(-1, 1, -20, 20, 1.5, 50.0);
  //glOrtho(-1, 1, -1, 1, 1.5, 50.0);
  gluPerspective(60, 1, 1.5, 80.0);
  
  height = field->getHeight();
  width = 4.0;
  length = 4.0;
  matrix = std::vector<std::vector<char>>(height);
  for (int i = 0; i < height; ++i) {
    matrix[i] = std::vector<char>(width*2 +length*2 - 4, CLEAR);
  }
}

void GlutDrawer::updateField(Drawable* field) {
  unsigned char** shape = field->getShape();
  for(int i = 0; i < field->getHeight()-1; i++)
    for(int j = 0; j < field->getWidth(); j++)
      matrix[i][j] = shape[i][j];
}

void GlutDrawer::updateActivePiece(Drawable* piece, int y, int x){
  int dimention = piece->getHeight();
  unsigned char** shape = piece->getShape();
  // initialize lastShape
  if(lastShape == NULL){
    lastShape = (unsigned char**)malloc(dimention * sizeof(unsigned char*));
    for (int i = 0; i < dimention; ++i) {
      lastShape[i] = (unsigned char*)malloc(dimention * sizeof(unsigned char));
    }
  }

  // clear on last position/rotation;
  if(piece == lastPiece)
    for(int i = 0; i < dimention; i++)
      for(int j = 0; j < dimention; j++)
        if(lastShape[i][j] != 0)
          matrix[lastX + i][lastY + j] = CLEAR;

  // draw the piece
  for(int i = 0; i < dimention; i++) {
    for(int j = 0; j < dimention; j++) {
      if (x == 0 && i == 0) {
        lastShape[i][j] = 0;
      } else {
        lastShape[i][j] = shape[i][j];

        if(shape[i][j] != 0) {
          matrix[x + i][y + j] = shape[i][j];
        }
      }
    }
  }

  //update angle
  angle = 30*y + 90;

  //Memorize last values
  lastPiece = piece;
  lastX = x;
  lastY = y;
}

void GlutDrawer::updateNext(Drawable* piece){
  // TODO
  return;
}

void GlutDrawer::updateScore(int value) {
  // TODO
  return;
}

void GlutDrawer::showGameOver() {
  // TODO
  return;
}

void GlutDrawer::showPause() {
  // TODO
  return;
}

void GlutDrawer::display() {
  //prints the field bounds
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float x = sin(drawer->angle*PI/180)*DISTANCE;
  float z = cos(drawer->angle*PI/180)*DISTANCE;
  gluLookAt(x, 13, z, 0, 9, 0, 0, 1, 0);
  //gluLookAt(x, y, z, 0, height_size/2, height_size/2, 0, 1, 0);

  glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5, 0.5, 0.5, 0.5);
    glScalef(drawer->width,0,drawer->length);
    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,drawer->height,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 0.75, 0.8, 0.5);
    glScalef(drawer->width,0,drawer->length);
    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,drawer->height/2.0,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glScalef(drawer->width,drawer->height,drawer->length);
    glutWireCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,drawer->height/2.0,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glScalef(drawer->width-2,drawer->height,drawer->length-2);
    glutWireCube(1.0);
  glPopMatrix();

  //draws the game
  for(int i = 0; i < drawer->width; i++){
    for(int j = 0; j < drawer->height; j++){
      for (int z = 0; z < drawer->length; z++){
        if(i == 0 || i == drawer->width-1 || z == 0 || z == drawer->length-1){
          char colorPosition = getColorPosition(i,j,z);
          if (colorPosition != CLEAR){
            glPushMatrix();
              glTranslatef(drawer->width-z-2.5,drawer->height-j-0.5,drawer->length-i-2.5);
              glEnable(GL_BLEND);
              glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
              setColor(colorPosition);
              glScalef(1, 1, 1);
              glutSolidCube(1.0);
              glColor4f(0.5, 0.5, 0.5, 1);
              glutWireCube(1.0);
            glPopMatrix();
          }
        }
      }
    }
  }

  //prints the UI
  //TODO

  //player name
  //TODO

  //score
  //TODO

  //next tetromino label
  //TODO

  //help text
  //TODO

  glFlush();
  glutSwapBuffers();
}

char GlutDrawer::getColorPosition(int x, int y, int z) {
  if (z == 0)
    return drawer->matrix[y][x];
  else if (x == drawer->width - 1)
    return drawer->matrix[y][x+z];
  else if (z == drawer->length - 1)
    return drawer->matrix[y][drawer->width*drawer->length-4-x-z];
  else if (x == 0)
    return drawer->matrix[y][drawer->width*drawer->length-4-z];
}

void GlutDrawer::setColor(char color) {
  switch(color)
  {
    case BLACK     : glColor4f(0, 0, 0, 1); break;
    case RED       : glColor4f(1, 0, 0, 1); break;
    case GREEN     : glColor4f(0, 1, 0, 1); break;
    case YELLOW    : glColor4f(1, 1, 0, 1); break;
    case NAIVE_BLUE: glColor4f(0, 0, 0.5, 1); break;
    case PURPLE    : glColor4f(1, 0, 1, 1); break;
    case BLUE      : glColor4f(0, 0, 1, 1); break;
    case WHITE     : glColor4f(1, 1, 1, 1); break;
    case CLEAR     : break;
    default: break;
  }
}