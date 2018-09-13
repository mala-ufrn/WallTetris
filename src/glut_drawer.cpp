#include "../include/glut_drawer.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::to_string;

#define FPS 120

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

const int GlutDrawer::CAMERA_REFRESH_MSEC = 1 * 1000 / FPS;

GlutDrawer::GlutDrawer() {
  lastX = lastY = 0;
  lastShape = NULL;
  lastPiece = NULL;
  angle = 90;
}


void GlutDrawer::init(string player, Drawable* field) {
  drawer = this;
  glClearColor(0.3, 0.3, 0.3, 0.0);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
              
  string playerStr = "Player: " + player;
  playerStr.copy(playerLabel, playerStr.size());
  strncpy( scoreLabel, "Score: 0", 8);
  height = field->getHeight();
  width = 4.0;
  length = 4.0;
  fieldMatrix = std::vector<std::vector<char>>(height);
  for (int i = 0; i < height; ++i) {
    fieldMatrix[i] = std::vector<char>(width*2 +length*2 - 4, CLEAR);
  }
}

void GlutDrawer::updateField(Drawable* field) {
  unsigned char** shape = field->getShape();
  for(int i = 0; i < field->getHeight(); i++)
    for(int j = 0; j < field->getWidth(); j++)
      fieldMatrix[i][j] = shape[i][j];
}

void GlutDrawer::updateActivePiece(Drawable* piece, int x, int y){
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
          fieldMatrix[lastY + i][(lastX + j)%12] = CLEAR;

  // draw the piece
  for(int i = 0; i < dimention; i++) {
    for(int j = 0; j < dimention; j++) {
      if (y+i == 0) {
        lastShape[i][j] = 0;
      } else {
        lastShape[i][j] = shape[i][j];

        if(shape[i][j] != 0) {
          fieldMatrix[y + i][(x + j)%12] = shape[i][j];
        }
      }
    }
  }

  //update angle
  //angle = 30*x + 90;

  //Memorize last values
  lastPiece = piece;
  lastX = x;
  lastY = y;
}

void GlutDrawer::updateNext(Drawable* piece){
  unsigned char** shape = piece->getShape();
  for(int i = 0; i < piece->getHeight(); i++) {
    for(int j = 0; j < piece->getWidth(); j++) {
      next[i][j] = shape[i][j];
    }
  }
  return;
}

void GlutDrawer::updateScore(int value) {
  string scoreStr = "Score: " + to_string(value);
  scoreStr.copy(scoreLabel, scoreStr.size());
  return;
}

void GlutDrawer::showGameOver() {
  exit(0);
  return;
}

void GlutDrawer::showPause() {
  // TODO
  return;
}

void GlutDrawer::display() {
  //prints the field bounds
  glClearColor(0.3, 0.3, 0.3, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(100, 0, 300, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 0.5, 1.5, 80.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float x = sin(drawer->angle*PI/180)*DISTANCE;
  float z = cos(drawer->angle*PI/180)*DISTANCE;
  gluLookAt(x, 13, z, 0, 9, 0, 0, 1, 0);

  //draws the field and active tetrominoes
  for(int i = 0; i < drawer->width; i++){
    for(int j = 0; j < drawer->height; j++){
      for (int z = 0; z < drawer->length; z++){
        if(i == 0 || i == drawer->width-1 || z == 0 || z == drawer->length-1){
          char colorPosition = getColorPosition(i,j,z);
          if (colorPosition != CLEAR){
            glPushMatrix();
              glTranslatef(drawer->width-z-2.5,drawer->height-j-0.5,drawer->length-i-2.5);
              setColor(colorPosition);
              glScalef(1, 1, 1);
              glutSolidCube(0.98);
              glColor4f(0.0, 0.0, 0.0, 1);
              glutWireCube(1.0);
            glPopMatrix();
          }
        }
      }
    }
  }

  //draws the field shape
  glPushMatrix();
    glColor4f(0.5, 0.5, 0.5, 0.5);
    glScalef(drawer->width,0,drawer->length);
    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,drawer->height-1,0);
    glColor4f(1, 0.75, 0.8, 0.5);
    glScalef(drawer->width,0,drawer->length);
    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,drawer->height/2.0,0);
    glColor4f(0.8, 0.8, 0.8, 0.3);
    glTranslatef(0,-0.5,0);
    glScalef(drawer->width,drawer->height-1,drawer->length);
    glutWireCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,drawer->height/2.0-0.5,0);
    glColor4f(0.5, 0.5, 0.5, 0.3);
    glScalef(drawer->width-2,drawer->height-1,drawer->length-2);
    glutSolidCube(1.0);
  glPopMatrix();

  //Draws the next tetromino
  glViewport(405, 260, 140, 140);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 5, -1, 5, -5, 10);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(-0.5, 0.5, 6, 0, 0, 0, 0, 1, 0);

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if (drawer->next[i][j] != CLEAR){
        glPushMatrix();
          glTranslatef(j, 4-i,0);
          setColor(drawer->next[i][j]);
          glScalef(1, 1, 1);
          glutSolidCube(0.98);
          glColor4f(0.0, 0.0, 0.0, 1);
          glutWireCube(1.0);
        glPopMatrix();
      }
    }
  }
  
  //Draws the UI texts
  glViewport(400, 0, 300, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 10, -17, 3, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor4f(0.9, 0.9, 0.9, 1.0);
  
  float fontRatio = 1/152.38;

  //player name
  int plNmSize = strlen(drawer->playerLabel);
  glPushMatrix();
    glTranslatef(0,-1,0);
    glScalef(fontRatio, fontRatio, 1);
    for(int i = 0; i < plNmSize; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, drawer->playerLabel[i]);
    }
  glPopMatrix();

  //player score
  int scLbSize = strlen(drawer->scoreLabel);
  glPushMatrix();
    glTranslatef(0,-2.5,0);
    glScalef(fontRatio, fontRatio, 1);
    for(int i = 0; i < scLbSize; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, drawer->scoreLabel[i]);
    }
  glPopMatrix();

  //Next label
  char nextLabel[] = "Next:";
  glPushMatrix();
    glTranslatef(0,-4,0);
    glScalef(fontRatio, fontRatio, 1);
    for(int i = 0; i < 5; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, nextLabel[i]);
    }
  glPopMatrix();

  //help text
  char helpLabel0[] = "Commands:";
  glPushMatrix();
    glTranslatef(0,-10,0);
    glScalef(0.7 * fontRatio, 0.7 * fontRatio, 1);
    for(int i = 0; i < 9; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, helpLabel0[i]);
    }
  glPopMatrix();

  char helpLabel1[] = "A: left";
  glPushMatrix();
    glTranslatef(0,-10.9,0);
    glScalef(0.7 * fontRatio, 0.7 * fontRatio, 1);
    for(int i = 0; i < 7; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, helpLabel1[i]);
    }
  glPopMatrix();

  char helpLabel2[] = "D: right";
  glPushMatrix();
    glTranslatef(0,-11.8,0);
    glScalef(0.7 * fontRatio, 0.7 * fontRatio, 1);
    for(int i = 0; i < 8; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, helpLabel2[i]);
    }
  glPopMatrix();

  char helpLabel3[] = "W: roll";
  glPushMatrix();
    glTranslatef(0,-12.7,0);
    glScalef(0.7 * fontRatio, 0.7 * fontRatio, 1);
    for(int i = 0; i < 7; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, helpLabel3[i]);
    }
  glPopMatrix();

  char helpLabel4[] = "S: speed up";
  glPushMatrix();
    glTranslatef(0,-13.6,0);
    glScalef(0.7 * fontRatio, 0.7 * fontRatio, 1);
    for(int i = 0; i < 11; i++){
      if(i == 9){
        glTranslatef(-0.2/fontRatio,0,0);
      }
      glutStrokeCharacter(GLUT_STROKE_ROMAN, helpLabel4[i]);
    }
  glPopMatrix();

  char helpLabel5[] = "P: pause";
  glPushMatrix();
    glTranslatef(5,-10.9,0);
    glScalef(0.7 * fontRatio, 0.7 * fontRatio, 1);
    for(int i = 0; i < 8; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, helpLabel5[i]);
    }
  glPopMatrix();
  
  char helpLabel6[] = "Q: quit";
  glPushMatrix();
    glTranslatef(5,-11.8,0);
    glScalef(0.7 * fontRatio, 0.7 * fontRatio, 1);
    for(int i = 0; i < 7; i++){
      glutStrokeCharacter(GLUT_STROKE_ROMAN, helpLabel6[i]);
    }
  glPopMatrix();

  glutSwapBuffers();
  glFlush();
}

char GlutDrawer::getColorPosition(int x, int y, int z) {
  if (z == 0)
    return drawer->fieldMatrix[y][x];
  else if (x == drawer->width - 1)
    return drawer->fieldMatrix[y][x+z];
  else if (z == drawer->length - 1)
    return drawer->fieldMatrix[y][drawer->width*drawer->length-4-x-z];
  else if (x == 0)
    return drawer->fieldMatrix[y][drawer->width*drawer->length-4-z];
}

void GlutDrawer::setColor(char color) {
  switch(color)
  {
    case BLACK     : glColor4f(0.0, 0.0, 0.0, 1.0); break;
    case RED       : glColor4f(0.8, 0.3, 0.3, 1.0); break;
    case GREEN     : glColor4f(0.1, 0.8, 0.1, 1.0); break;
    case YELLOW    : glColor4f(0.9, 0.9, 0.0, 1.0); break;
    case NAIVE_BLUE: glColor4f(0.2, 0.4, 0.9, 1.0); break;
    case ORANGE    : glColor4f(1.0, 0.5, 0.0, 1.0); break;
    case PURPLE    : glColor4f(0.7, 0.3, 0.8, 1.0); break;
    case BLUE      : glColor4f(0.0, 0.7, 0.9, 1.0); break;
    case WHITE     : glColor4f(1.0, 1.0, 1.0, 1.0); break;
    case CLEAR     : break;
    default: break;
  }
}

void GlutDrawer::timer(int value) {
  int camMove = 30, maxCamMove = 360/camMove + 1;
  int angle2 = ((int)drawer->lastX * camMove + 90) % 360;
  drawer->angle = (value + (int)drawer->angle) % 360;
  drawer->angle = drawer->angle < 0 ? 360 + drawer->angle : drawer->angle;
  int signal = (abs(angle2 - drawer->angle) <= 180) ? 1 : -1;
  int velocity = signal == 1 ? abs(angle2 - drawer->angle)/camMove + 1: maxCamMove - abs(angle2 - drawer->angle)/camMove;

  if(angle2 < drawer->angle)
    value = -2*signal*velocity;
  else if(angle2 > drawer->angle)
    value = 2*signal*velocity;
  else
    value = 0;
  
  glutPostRedisplay();
  glutTimerFunc(CAMERA_REFRESH_MSEC ,timer, value);
}
