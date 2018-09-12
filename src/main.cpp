#include "../include/game.h"
#include "../include/bash_printer.h"
#include "../include/glut_drawer.h"

#include <iostream>

#include <GL/glut.h>
#include <time.h>

int main(int argc, char *argv[]) {
  Game* game;
  srand(time(NULL));

  // Read the argument parameter
  char tetris_type = 'W';
  if (argc > 1) {
    tetris_type = argv[1][0];
    if (tetris_type != 'B' && tetris_type != 'W') {
      std::cout << "Invalid tetris type. Pass B for Bash Tetris or W"
      << " for Wall Tetris" << std::endl; 
      return 1;
    }
  }

  if (tetris_type == 'B') {
    // Bash Version
    game = new Game(new BashPrinter());
    game->init(true);
    while(game->isPlaying()) {
      game->update();
    }
  } else {
    // OpenGL Version
    game = new Game(new GlutDrawer());
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Wall Tetris");
    glutKeyboardFunc(&Game::keyboard);
    glutDisplayFunc(&GlutDrawer::display);
    glutTimerFunc(1, &GlutDrawer::timer, 0);
    glutIdleFunc([]() { 
      Game::idleFunc();
      glutPostRedisplay(); 
    });

    game->init();
    glutMainLoop();
  }

  delete game;
  return 0;
}
