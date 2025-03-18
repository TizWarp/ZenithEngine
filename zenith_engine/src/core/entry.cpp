#include "entry.hpp"
#include "../zenith.hpp"
#include "ecs.hpp"
#include "glm/fwd.hpp"
#include "renderer/renderer.hpp"
#include "window.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cstdio>
#include "../ecs_modules/camera.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


using namespace Zenith;

bool running = true;


int main() {



  Window::initWindow("TEST", 600, 400);


  if (!Renderer::initRenderer()){
    return 4;
  }


  ECS::get()->registerComponent<Position>();
  ECS::get()->registerComponent<Camera>();
  ECS::get()->addResource(Keys());

  Keys* keys = ECS::ResourceQuery<Keys>().get();

  Zenith::z_main(ECS::get());

  while (running) {

    Window::pollEvents(&running, keys);
    ECS::get()->update();

    Renderer::beginFrame();
    Renderer::drawFrame(ECS::get());

    Window::swapBuffers();
    keys->update();
  }
}
