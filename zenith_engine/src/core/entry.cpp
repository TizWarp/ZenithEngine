#include "entry.hpp"
#include "../zenith.hpp"
#include "ecs.hpp"
#include "renderer.hpp"
#include "spdlog/spdlog.h"
#include "window.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cstdio>

using namespace Zenith;

bool running = true;


int main() {


  Zenith::z_main(ECS::get());

  Window::initWindow("TEST", 600, 400);


  if (!Renderer::initRenderer()){
    return 4;
  }


  ECS::get()->addResource(Keys());

  Keys* keys = ECS::ResourceQuery<Keys>().get();

  while (running) {

    Window::pollEvents(&running, keys);
    ECS::get()->update();

    Renderer::beginFrame();
    Renderer::drawFrame();

    Window::swapBuffers();
    keys->update();
  }
}
