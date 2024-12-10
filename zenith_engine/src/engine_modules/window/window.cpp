#include <GL/glew.h>
#include "window.hpp"
#include "../../zenith.hpp"
#include "spdlog/spdlog.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <cstdio>
#include "../input/input.hpp"
namespace Zenith {

void windowEventsSys(ECS::ResourceQuery<GameState> gs_state, ECS::ResourceQuery<Keys> keys_query);
void windowSwapSys(ECS::ComponentQuery<Window> window_query);

WindowModule::WindowModule() {
  ECS *ecs = ECS::get();

  ecs->enableModule<InputModule>();

  ecs->registerComponent<Window>();
  ecs->addSystem(0, windowEventsSys);
  ecs->addSystem(127, windowSwapSys);
}

void windowEventsSys(ECS::ResourceQuery<GameState> gs_state, ECS::ResourceQuery<Keys> keys_query) {
  SDL_Event event;
  
  GameState *gs = gs_state.get();
  Keys* keys = keys_query.get();

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      gs->running = false;
      break;
    case SDL_EVENT_KEY_UP:
      if (!event.key.repeat){
        keys->keyUp(SDL_GetKeyName(event.key.key));
      }
      break;
    case SDL_EVENT_KEY_DOWN:
      if (!event.key.repeat){
        keys->keyDown(SDL_GetKeyName(event.key.key));
      }
      break;
    default:
      break;
    }
  }
}

void windowSwapSys(ECS::ComponentQuery<Window> window_query) {
  for (auto t : window_query.components) {
    Window *window = t.get<0>();

    SDL_GL_SwapWindow(window->getWindow());
  }
}

Window::Window(const char *title, i32 width, i32 height) {
  window = SDL_CreateWindow(title, width, height,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (window == NULL) {
    Logger::error("Error creating sdl window '{}'", SDL_GetError());
    return;
  }
  gl_context = SDL_GL_CreateContext(window);
  if (gl_context == NULL) {
    Logger::error("Error creating gl context '{}'", SDL_GetError());
    return;
  }
}

SDL_Window *Window::getWindow() { return window; }

} // namespace Zenith
