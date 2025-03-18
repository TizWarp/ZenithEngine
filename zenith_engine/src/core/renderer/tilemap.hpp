#pragma once

namespace Zenith{
  namespace Renderer{
    class TileMap{
      public:


        const float VERTICES[16] = {
          -0.5f, 0.5f, 0.0f, 1.0f,
          0.5f, 0.5f, 1.0f, 1.0f,
          0.5f, -0.5f, 1.0f, 0.0f,
          -0.5f, -0.5f, 0.0f, 0.0f,
        };

        const unsigned int INDICES[6] = {
          0, 1, 2,
          0, 3, 2,
        };



      private:
    };
  }
}
