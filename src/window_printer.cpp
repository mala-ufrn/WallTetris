#include "../include/window_printer.h"

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
#define distance 22

//Colors to printer output
enum Color {
  CLEAR = 0,
  BLACK = 30,
  RED = 114,
  GREEN = 103,
  YELLOW = 121,
  NAIVE_BLUE = 110,
  PURPLE = 112,
  BLUE = 98,
  WHITE = 119
};

int WindowPrinter::height;
int WindowPrinter::length;
int WindowPrinter::width;
float WindowPrinter::angle;
std::vector<std::vector<char>> WindowPrinter::matrix;

WindowPrinter::WindowPrinter() {
  lastX = lastY = 0;
  lastShape = NULL;
  lastPiece = NULL;
}


void WindowPrinter::init(string player, Drawable* field) {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Wall Tetris");
  glutDisplayFunc(display);
  
  height = field->getHeight()-1;
  width = 4.0;
  length = 4.0;
  matrix = std::vector<std::vector<char>>(height);
  for (int i = 0; i < height; ++i)
    matrix[i] = std::vector<char>(width*2 +length*2 - 4, CLEAR);
}

void WindowPrinter::display() {
  //prints the field bounds
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float x = sin(angle*PI/180)*distance;
  float z = cos(angle*PI/180)*distance;
  gluLookAt(x, 15, z, 0, 12, 0, 0, 1, 0);
  //gluLookAt(x, y, z, 0, height_size/2, height_size/2, 0, 1, 0);

  glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5, 0.5, 0.5, 0.5);
    glScalef(width,0,length);
    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,height,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 0.75, 0.8, 0.5);
    glScalef(width,0,length);
    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,height/2.0,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, 0.5);
    glScalef(width,height,length);
    glutWireCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,height/2.0,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, 0.5);
    glScalef(width-2,height,length-2);
    glutWireCube(1.0);
  glPopMatrix();

  //print game
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      for (int z = 0; z < length; z++){
        if(i == 0 || i == width-1 || z == 0 || z == length-1){
          char colorPosition = getColorPosition(i,j,z);
          if (colorPosition != CLEAR){
            glPushMatrix();
              glTranslatef(width-z-2.5,height-j-0.5,length-i-2.5);
              glEnable(GL_BLEND);
              glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
              setColor(colorPosition);
              glScalef(1,1,1);
              glutSolidCube(1.0);
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

void WindowPrinter::updateField(Drawable* field) {
  unsigned char** shape = field->getShape();
  for(int i = 0; i < field->getHeight()-1; i++)
    for(int j = 0; j < field->getWidth(); j++)
      matrix[i][j] = shape[i+1][j];
}

void WindowPrinter::updateActivePiece(Drawable* piece, int y, int x){
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
          matrix[lastX + j + 1][lastY + i] = CLEAR;

  // draw the piece
  for(int i = 0; i < dimention; i++) {
    for(int j = 0; j < dimention; j++) {
      if (y == 0 && i == 0) {
        lastShape[i][j] = 0;
      } else {
        lastShape[i][j] = shape[i][j];

        if(shape[i][j] != 0) {
          matrix[x + j + 1][y + i] =  shape[i][j];
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

void WindowPrinter::updateNext(Drawable* piece){
  return;
}

void WindowPrinter::updateScore(int value) {
  return;
}

void WindowPrinter::showGameOver() {
  return;
}

void WindowPrinter::showPause() {
  return;
}

char WindowPrinter::getColorPosition(int x, int y, int z) {
  if (z == 0)
    return matrix[y][x];
  else if (x == width - 1)
    return matrix[y][x+z];
  else if (z == length - 1)
    return matrix[y][width*length-4-x-z];
  else if (x == 0)
    return matrix[y][width*length-4-z];
}

void WindowPrinter::setColor(char color) {
  switch(color)
  {
    case BLACK     : glColor4f(0, 0, 0, 0.5); break;
    case RED       : glColor4f(1, 0, 0, 0.5); break;
    case GREEN     : glColor4f(0, 1, 0, 0.5); break;
    case YELLOW    : glColor4f(1, 1, 0, 0.5); break;
    case NAIVE_BLUE: glColor4f(0, 0, 0.5, 0.5); break;
    case PURPLE    : glColor4f(1, 0, 1, 0.5); break;
    case BLUE      : glColor4f(0, 0, 1, 0.5); break;
    case WHITE     : glColor4f(1, 1, 1, 0.5); break;
    case CLEAR     : break;
    default: break;
  }
}