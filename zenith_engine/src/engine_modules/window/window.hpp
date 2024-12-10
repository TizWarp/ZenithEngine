#pragma once

#include "../../core/ecs.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

namespace Zenith{

  class Window{
    public:
  
      i32 x;
      i32 y;
      const char* title;

      Window(const char* title, i32 width, i32 height);
      Window() {};

      SDL_Window* getWindow();

      private:

      SDL_Window* window;
      SDL_GLContext gl_context;
  };

  class WindowModule : public ECS::IModule{
    public:
    WindowModule(const char* title = "Zenith", i32 width = 600, i32 height = 400);
  };


}
