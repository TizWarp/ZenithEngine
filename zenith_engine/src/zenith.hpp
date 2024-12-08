#pragma once

#include "core/entry.hpp"
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
extern void setupGame(Zenith::GameInfo &game_info);

namespace Zenith{
  namespace Logger = spdlog;
  namespace Math = glm;
}


