#pragma once
#include "../../core/ecs.hpp"


namespace Zenith{


  class Sprite {
    public:


    private:

    unsigned int VBO, EBO, TEX;

    const float vertices[20] = {
      -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
      -0.25f, -0.25f, 0.0f, 0.0f, 0.0f,
      0.25f, 0.25f, 0.0f, 1.0f, 1.0f,
      0.25, -0.25f, 0.0f, 1.0f, 0.0f
    };
    const u32 indicies[6] {
      2, 0, 1,
      2, 3, 1,
    };
  };

  class OpenGLModule : public ECS::IModule{
    public:
      OpenGLModule();
  };
}
