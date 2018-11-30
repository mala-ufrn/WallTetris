#include "../include/game.h"
#include "../include/glut_drawer.h"

#include <iostream>

#include <GL/glut.h>
#include <time.h>

int main(int argc, char *argv[]) {
  srand(time(NULL));

  Game*game = new Game(new GlutDrawer());
    
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("Wall Tetris");
  glutKeyboardFunc(&Game::keyboard);
  glutKeyboardUpFunc(&Game::keyboardUp);
  glutDisplayFunc(&GlutDrawer::display);
  glutTimerFunc(GlutDrawer::CAMERA_REFRESH_MSEC, &GlutDrawer::rollCamera, 0);
  glutTimerFunc(Game::STD_UPDATE_MSEC ,&Game::idleFunc, 0);
  glutIdleFunc([]() { 
    glutPostRedisplay(); 
  });
  game->init();
  
  glutMainLoop();

  delete game;
  return 0;
}
