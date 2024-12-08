#include "window.hpp"
#include "events.hpp"
#include "../zenith.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <csignal>
#include <string>

namespace Zenith::Window {

SDL_Window *window = nullptr;
SDL_GLContext gl_context;

bool createWindow(std::string window_name, int width, int height) {
  window = SDL_CreateWindow(window_name.c_str(), width, height,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if (window == NULL) {
    /*Logger::error("Error creating sdl3 window '{}'", SDL_GetError());*/
    return false;
  }

  gl_context = SDL_GL_CreateContext(window);

  SDL_GL_MakeCurrent(window, gl_context);

  SDL_ShowWindow(window);

  return true;
}
void getWindowSize(int &width, int &height) {
  SDL_GetWindowSize(window, &width, &height);
}
void closeWindow() {
  SDL_GL_DestroyContext(gl_context);
  SDL_DestroyWindow(window);
}
void pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      Events::fireEvent(Events::QUIT, Events::EventContext{});
      break;

    default:
      break;
    }
  }
}
SDL_Window *getWindow() { return window; }
} // namespace Zenith::Window
