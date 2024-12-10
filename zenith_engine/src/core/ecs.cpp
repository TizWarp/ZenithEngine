#include "ecs.hpp"
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>

namespace Zenith {

ECS ECS::instance = ECS();

ECS *ECS::get() { return &ECS::instance; }

static void queueEntityDelete(Entity entity);

Entity ECS::createEntity() {
  static u64 entity_count = 0;
  Entity new_entity;
  if (unused_entity_ids.empty()) {
    entity_count += 1;
    new_entity = entity_count - 1;
  } else {
    Entity new_entity = unused_entity_ids[unused_entity_ids.size() - 1];
    unused_entity_ids.pop_back();
  }
  return new_entity;
}

void ECS::update() {

  for (std::vector<ISystem *> sys_vec : systems) {
    for (ECS::ISystem *sys : sys_vec) {
      sys->call();
    }
  }
}

void ECS::removeEntity(Entity entity) {
  for (IComponentPool *pool : ECS::component_pools) {
    pool->removeEntityComponent(entity);
  }
}

} // namespace Zenith
