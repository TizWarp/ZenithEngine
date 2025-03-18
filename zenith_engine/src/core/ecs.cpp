#include "ecs.hpp"
#include "spdlog/spdlog.h"
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <shared_mutex>

namespace Zenith {

ECS ECS::instance = ECS();

ECS *ECS::get() { return &ECS::instance; }

static void queueEntityDelete(Entity entity);

Entity ECS::createEntity() {
  Entity new_entity;
  if (unused_entity_ids.empty()) {
    entity_counter += 1;
    new_entity = entity_counter - 1;
  } else {
    Entity new_entity = unused_entity_ids[unused_entity_ids.size() - 1];
    unused_entity_ids.pop_back();
  }
  return new_entity;
}

void ECS::update() {
  if (update_queries_flag) {
    updateQueryCache();
    update_queries_flag = false;
  }
  for (std::unique_ptr<ISystem> &sys : systems) {
    sys->call();
  }
}

void ECS::removeEntity(Entity entity) {
  for (std::unique_ptr<IComponentPool> &pool : ECS::component_pools) {
    pool->removeEntityComponent(entity);
  }
}

} // namespace Zenith
