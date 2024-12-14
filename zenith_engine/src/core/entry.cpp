#include "entry.hpp"
#include "../zenith.hpp"
#include "SDL3/SDL.h"
#include "ecs.hpp"
#include "window.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cstdio>

using namespace Zenith;

bool running = true;

int main() {

  Zenith::z_main();

  Window::initWindow("TEST", 600, 400);

  ECS::get()->addResource(Keys());

  Keys* keys = ECS::ResourceQuery<Keys>().get();

  while (running) {

    Window::pollEvents(&running, keys);
    ECS::get()->update();

    Window::swapBuffers();
    keys->update();
  }
}
