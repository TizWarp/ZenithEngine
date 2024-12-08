#pragma once
#include <fmt/base.h>
#include <string>
#include <glm/glm.hpp>

namespace Zenith{


  namespace Math = glm;

  struct GameInfo{

    std::string game_name = "Game";
    Math::vec4 clear_color = Math::vec4(0.0f, 0.0f, 0.0f, 0.0f);
  };

  static GameInfo gameInfo;

}
