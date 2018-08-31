#include "../include/game.h"
#include "../include/bash_printer.h"
#include "../include/window_printer.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

Game *game;

int main(int argc, char *argv[]) {
  char tetris_type = 'W';

  if (argc > 1) {
    tetris_type = argv[1][0];
    if (tetris_type != 'B' && tetris_type != 'W') {
      std::cout << "Invalid tetris type. Pass B for Bash Tetris or W for Wall Tetris" << std::endl; 
      return 1;
    }
  }

  if (tetris_type == 'B') {
    game = new Game(new BashPrinter());
    game->init();
    while(game->isPlaying()) {
      game->update();
    }
  } else {
    
    srand(time(NULL));
    glutInit(&argc, argv);
    game = new Game(new WindowPrinter());
    game->init();
    glutKeyboardFunc(game->keyboard);
    glutIdleFunc([]()
    {
      if(game->isPlaying())
        game->update();
      else
        exit(-1);
      glutPostRedisplay();
    });
    
    //cor de fundo eh cinza
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    //alterne e altere as projecoes para alcancar os resultados desejados
    //glFrustum(-1, 1, -20, 20, 1.5, 20.0);
    //glOrtho(-1, 1, -1, 1, 1.5, 100.0);
    gluPerspective(60, 1, 1.5, 80.0);

    glutMainLoop();

  }

  delete game;
  std::cout << "Thank you for playing." << std::endl;
  return 0;
}