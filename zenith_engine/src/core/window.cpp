#include "window.hpp"
#include "../zenith.hpp"
#include "defines.hpp"
#include "ecs.hpp"
#include "entry.hpp"
#include "../ecs_modules/input.hpp"
#include "spdlog/spdlog.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_video.h>
#include <cstdio>
namespace Zenith {

namespace Window {

static SDL_Window *window;
static SDL_GLContext gl_context;

void pollEvents(bool *running, Keys* keys) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        *running = false;
        break;
      case SDL_EVENT_KEY_UP:
        if (!event.key.repeat)
          keys->keyUp(SDL_GetKeyName(event.key.key));
        break;
      case SDL_EVENT_KEY_DOWN:
        if (!event.key.repeat){
          keys->keyDown(SDL_GetKeyName(event.key.key));
        }
    default:
      break;
    }
  }
}

bool initWindow(const char *name, int width, int height) {

  if (window != NULL) {
    return true;
  }

  window = SDL_CreateWindow(name, width, height,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if (window == NULL) {
    Logger::error("Error starting sdl window '{}'", SDL_GetError());
    return false;
  }

  gl_context = SDL_GL_CreateContext(window);
  if (gl_context == NULL) {
    Logger::error("Error create gl context '{}'", SDL_GetError());
    return false;
  }

  return true;
}

void swapBuffers() { SDL_GL_SwapWindow(window); }

void getSize(int *width, int *height) {
  SDL_GetWindowSize(window, width, height);
}

} // namespace Window
} // namespace Zenith
