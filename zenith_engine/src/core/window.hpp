#pragma once

#include <string>
#include <SDL3/SDL.h>

namespace Zenith::Window{
   bool createWindow(std::string window_name, int width, int height);
   void getWindowSize(int &width, int &height);
   void closeWindow();
   void pollEvents();
   SDL_Window* getWindow();
}
