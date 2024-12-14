#pragma once
#include "../ecs_modules/input.hpp"

namespace Zenith{
  namespace Window{
    bool initWindow(const char* name, int width, int height);

    void pollEvents(bool *running, Keys *keys);

    void getSize(int *width, int * height);

    void swapBuffers();
  }
}
