#ifndef CODESKETCH_CORE_SKETCH_H
#define CODESKETCH_CORE_SKETCH_H

#include <string>

#include <SDL2/SDL.h>

#define READ  0
#define WRITE 1

namespace codesketch {

const int keys[] = {
  // Letters
  SDL_SCANCODE_A, SDL_SCANCODE_B, SDL_SCANCODE_C, SDL_SCANCODE_D,
  SDL_SCANCODE_E, SDL_SCANCODE_F, SDL_SCANCODE_G, SDL_SCANCODE_H,
  SDL_SCANCODE_I, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L,
  SDL_SCANCODE_M, SDL_SCANCODE_N, SDL_SCANCODE_O, SDL_SCANCODE_P,
  SDL_SCANCODE_Q, SDL_SCANCODE_R, SDL_SCANCODE_S, SDL_SCANCODE_T,
  SDL_SCANCODE_U, SDL_SCANCODE_V, SDL_SCANCODE_W, SDL_SCANCODE_X,
  SDL_SCANCODE_Y, SDL_SCANCODE_Z,

  // Numbers
  SDL_SCANCODE_0, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3,
  SDL_SCANCODE_4, SDL_SCANCODE_5, SDL_SCANCODE_6, SDL_SCANCODE_7,
  SDL_SCANCODE_8, SDL_SCANCODE_9,

  // Arrows
  SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT,

  SDL_SCANCODE_RETURN, SDL_SCANCODE_BACKSPACE,
  SDL_SCANCODE_SPACE, SDL_SCANCODE_DELETE,

  // F keys
  SDL_SCANCODE_F1, SDL_SCANCODE_F2, SDL_SCANCODE_F3, SDL_SCANCODE_F4,
  SDL_SCANCODE_F5, SDL_SCANCODE_F6, SDL_SCANCODE_F7, SDL_SCANCODE_F8,
  SDL_SCANCODE_F9, SDL_SCANCODE_F10, SDL_SCANCODE_F11, SDL_SCANCODE_F12,

  // Mod Keys
  SDL_SCANCODE_LSHIFT, SDL_SCANCODE_RSHIFT,
  SDL_SCANCODE_LCTRL, SDL_SCANCODE_RCTRL
};

const int keysSize = sizeof(keys)/sizeof(keys[0]);

enum {
  COMMAND_NOTHING,
  COMMAND_BACKGROUND,

  COMMAND_STROKECOLOR,
  COMMAND_POINT,
  COMMAND_LINE,
  COMMAND_RECT,

  COMMAND_TEXT,
  COMMAND_TEXTSIZE,
  COMMAND_TEXTCOLOR,

  // XXX(naum): Not implemented
  COMMAND_FILLCOLOR,
  COMMAND_STROKEWIDTH,
  COMMAND_CIRCLE,
  COMMAND_ELLIPSE,

  COMMAND_CAMERA,
  COMMAND_WINDOW,

  COMMAND_EXIT,

  COMMAND_NUM
};

bool sketchOpen(const std::string&);
void sketchClose();
bool sketchIsRunning();
void sketchSendData();
void sketchReceiveData();

}

#endif
