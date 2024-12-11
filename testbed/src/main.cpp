#include "core/defines.hpp"
#include "core/entry.hpp"
#include "engine_modules/input/input.hpp"
#include "engine_modules/window/window.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"
#include <core/ecs.hpp>
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>
#include <fstream>
#include <zenith.hpp>

using namespace Zenith;


struct Position{
  int x;
  int y;
};


void stress(ECS::ComponentQuery<Position> pos_query){
  /*printf("Calling stress %zu\n", pos_query.entities.size());*/
  ECS::get()->addEntityComponent(1, Position{});
  for (auto components : pos_query.components){
    for (auto components2 : pos_query.components){
      Position* pos1 = components.get<0>();
      Position* pos2 = components2.get<0>();

      if (pos1 == pos2){
        continue;
      }

      pos1->x = pos2->y;
      pos2->y = pos1->x;
    }
  }
}

void Zenith::z_main() {

  ECS *ecs = ECS::get();
  ecs->enableModule<WindowModule>("TEST");

  ecs->registerComponent<Position>();


  for (i32 i = 0; i < 1000; i++){
    Entity entity = ecs->createEntity();
    /*printf("Entity number is %zu\n", entity);*/
    ecs->addEntityComponent(entity, Position{});
  }

  ecs->addSystem(4, stress);

}
