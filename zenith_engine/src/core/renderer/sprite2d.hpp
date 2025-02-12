#pragma once

#include "texture.hpp"
#include <SDL3/SDL_keyboard.h>
namespace Zenith{
  class Sprite2D{
    public:
      Sprite2D(Texture2D texture);
      unsigned int texture;
    private:

  };
}
