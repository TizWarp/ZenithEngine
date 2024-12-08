#include "entry.hpp"
#include "events.hpp"
#include "window.hpp"
#include "../zenith.hpp"
#include <GL/glew.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <cmath>
#include <spdlog/spdlog.h>
#include "ecs.hpp"

using namespace Zenith;

namespace Zenith {
static bool running = true;
}

bool initSdl() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
    Logger::error("Error initializing SDL3 '{}'", SDL_GetError());
    return false;
  }

  return true;
}

bool initGlew() {

  glewExperimental = true;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    /*Logger::error("Failed to init glew '{}'", glewGetErrorString(glewError));*/
    return false;
  }

  return true;
}

bool quitCallback(Events::EventContext &ctx){

  running = false;

  return true;
}

int main() {

  setupGame(Zenith::gameInfo);
  Logger::info("Setup game");

  if (!initSdl()) {
    return -1;
  }

  if (!Window::createWindow(gameInfo.game_name, 600, 400)) {
    return -1;
  }

  if (!initGlew()) {
    return -1;
  }

  Events::addListener(Events::QUIT, (Events::Listener)0, quitCallback);

  while (running) {
    Window::pollEvents();

    ECS::ecsUpdate();

    glClearColor(gameInfo.clear_color.r, gameInfo.clear_color.g, gameInfo.clear_color.b, gameInfo.clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
    

    SDL_GL_SwapWindow(Window::getWindow());

  }

  return 0;
}
