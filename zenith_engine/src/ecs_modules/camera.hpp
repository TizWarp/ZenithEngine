#pragma once
#include "../core/defines.hpp"
#include "glm/fwd.hpp"

namespace Zenith{
  class Camera{
    public:
      Camera(float zoom);
      float zoom;   
  };
}
