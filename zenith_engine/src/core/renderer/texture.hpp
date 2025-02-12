#pragma once

namespace Zenith{
  class Texture2D{
    public:
      Texture2D(const char* image_path);
      ~Texture2D();



      unsigned int ID;
      int width, height;
  };
}
