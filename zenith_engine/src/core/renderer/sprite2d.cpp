#include "sprite2d.hpp"
#include "texture.hpp"

namespace Zenith{
  Sprite2D::Sprite2D(Texture2D texture){
    this->texture = texture.ID;
  }
}
