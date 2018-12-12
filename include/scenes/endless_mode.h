#ifndef ENDLESS_MODE_H
#define ENDLESS_MODE_H

#include <glm/glm.hpp>
#include <irrklang/irrKlang.h>
#include <vector>

#include "scene.h"
#include "scene_master.h"
#include "utils/shader.h"
#include "rendering/text_render.h"
#include "rendering/image_render.h"
#include "rendering/model_render.h"
#include "models/tetromino.h"
#include "models/field.h"

class EndlessMode : public Scene, public GameMaster {
private:

  SceneMaster *sceneMaster;

  bool jspresent;

  // Flags for comands
  bool rolling;
  bool moving;
  //Update current refresh time (ms)
  bool speedUp;
  // Flag for new game
  bool playing;
  // Flag for pause
  bool paused;
  // High Score
  int highScore;
  // Player score
  int score;
  // Game level
  int level;
  // Lines counter (Def. Level)
  int lines;

  float *scrFactor,
        *widePadding;

  glm::vec2 winOrigDims;

  //Game field
  Field* field;
  //Next tetromino
  Tetromino* nextTetr;
  //Active tetromino
  Tetromino* activeTetr;
  //Object that draws the game scene

  Shader *textShader,
         *imageShader,
         *quadShader,
         *gameWireShader,
         *uiWireShader,
         *gameBlockShader,
         *uiBlockShader;
  TextRender *sansPsx64,
             *sansKey64;
  ImageRender *backGround,
              *fieldBGround,
              *nextBGround;
  ModelRender *gameModelRender,
              *uiModelRender;

  irrklang::ISoundEngine *soundEngine;

  //Height of Wall Tetris
  int height;
  //Width of Wall Tetris
  int width;
  //Length of Wall Tetris
  int length;
  //Angle of horizontal visualization
  float horAngle;
  //Matrix of Wall Tetrix
  std::vector<std::vector<char>> fieldMatrix;
  //Piece last x
  int lastX;
  //Piece last y
  int lastY;
  //Piece last shape
  std::vector<std::vector<char>> lastShape;
  //active piece reference
  Drawable* lastPiece;
  //
  int value;
  //
  double lastTimeMoveDown;
  //
  double lastTimeMoveHoriz;
  //
  double lastTimeRoll;
  //
  bool pausePressed;
  //
  double pausedTimeMark;


public:
  EndlessMode(SceneMaster* sceneMaster, irrklang::ISoundEngine* soundEngine, const glm::vec2 win_dimentions, float* scrFact, float* wdPadd);
  ~EndlessMode();
  void createNextTetr(int posX);
  void increaseScore(int value);
  void increaseLines(int quantity);
  void gameOver();
  void updateField(Drawable *field);
  void updateActivePiece(Drawable *piece, glm::ivec2 pos);
  void processInputs(GLFWwindow *window);
  void rollCamera();
  void update();
  void draw();
};
#endif