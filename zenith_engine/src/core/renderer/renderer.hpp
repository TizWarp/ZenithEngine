#pragma once

#include "../ecs.hpp"

namespace Zenith{
  namespace Renderer{


    bool initRenderer();    

    void beginFrame();

    void drawFrame(ECS* ecs);

    void loadTexture();


    


  }
}
