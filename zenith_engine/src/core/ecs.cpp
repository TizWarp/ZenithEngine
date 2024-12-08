#include "ecs.hpp"
#include <vector>

namespace Zenith::ECS {

static std::vector<Entity> avaliable_entity_ids = {};
std::vector<IComponentPool *> component_pools = {};
static std::vector<Entity> entity_deletion_queue = {};
std::vector<Entity> entity_ids = {};
std::vector<IResource*> resources = {};

Entity createEntity() {
  static u64 entity_count = 0;
  Entity new_entity;
  if (avaliable_entity_ids.empty()) {
    entity_count += 1;
    entity_ids.push_back(entity_count - 1);
    new_entity = entity_count - 1;
  } else {
    Entity new_entity = avaliable_entity_ids[avaliable_entity_ids.size() - 1];
    avaliable_entity_ids.pop_back();
    entity_ids.push_back(new_entity);
  }
  return new_entity;
}

void removeEntity(Entity entity) {
  avaliable_entity_ids.push_back(entity);
  for (IComponentPool *pool : component_pools) {
    pool->removeEntityComponent(entity);
  }
}

void queueDelete(Entity entity) { entity_deletion_queue.push_back(entity); }

std::vector<ISystem *> systems = {};

void ecsUpdate() {
  for (ISystem *system : systems) {
    system->call();
  }

  for (Entity entity : entity_deletion_queue) {
    ECS::removeEntity(entity);
  }

  entity_deletion_queue.clear();
}
} // namespace Zenith::ECS
