#include "core/renderer/sprite2d.hpp"
#include "core/renderer/texture.hpp"
#include "ecs_modules/input.hpp"
#include <cstdio>
#include <zenith.hpp>

using namespace Zenith;

void Zenith::z_main(ECS* ecs) {
  Entity entity =  ecs->createEntity();
  printf("TEST\n");
  Texture2D tex = Texture2D("./zenith_engine/assets/images/wall.jpg");
  ecs->addEntityComponent(entity, Sprite2D(tex));
}
