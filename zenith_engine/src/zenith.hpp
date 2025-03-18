#pragma once

#include "core/entry.hpp"
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include "core/ecs.hpp"

namespace Zenith{

  namespace Logger = spdlog;
  namespace Math = glm;

  typedef vec2 Position;

  extern void z_main(ECS*);

}


