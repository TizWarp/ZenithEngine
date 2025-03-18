#include "core/ecs.hpp"
#include "core/renderer/sprite2d.hpp"
#include "core/renderer/texture.hpp"
#include "ecs_modules/camera.hpp"
#include "ecs_modules/input.hpp"
#include "glm/fwd.hpp"
#include <cstdio>
#include <regex>
#include <zenith.hpp>

using namespace Zenith;

void Zenith::z_main(ECS* ecs) {
  Entity entity =  ecs->createEntity();
  printf("TEST\n");
  Texture2D tex = Texture2D("./zenith_engine/assets/images/wall.jpg");
  ecs->addEntityComponent(entity, Sprite2D(tex));
  ecs->addEntityComponent(entity, Position(0.0f, 0.0f));

  Entity cam = ecs->createEntity();
  ecs->addEntityComponent(cam, Camera(0.0f));
  ecs->addEntityComponent(cam, Position(0.0f, 0.0f));

}



