#pragma once

#include "defines.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>
#include <functional>
#include <memory>
#include <shared_mutex>
#include <tuple>
#include <vector>
namespace Zenith {

typedef u64 Entity;

class IComponentPool {
public:
  virtual ~IComponentPool() {};
  virtual void removeEntityComponent(Entity entity) = 0;
};

template <typename C> class ComponentPool : public IComponentPool {
public:
  bool hasEntity(Entity entity) {
    /*printf("%d \n", getEntityIndex(entity));*/

    return getEntityIndex(entity) != -1;
  }

  unsigned int size() { return components.size(); }

  void addEntityComponent(Entity entity, C component) {
    if (!hasEntity(entity)) {
      components.push_back(component);
      entities.push_back(entity);
    }
    /*printf("%zu \n", components.size());*/
  }

  void removeEntityComponent(Entity entity) override {
    i32 index = getEntityIndex(entity);

    if (index == -1) {
      return;
    }

    components[index] = components[components.size() - 1];
    entities[index] = entities[entities.size() - 1];

    components.pop_back();
    entities.pop_back();
  }

  C *getEntityComponent(Entity entity) {
    i32 index = getEntityIndex(entity);
    if (index == -1) {
      return nullptr;
    }
    return &components[index];
  }

private:
  i32 getEntityIndex(Entity entity) {
    /*printf("%d entity id \n", entity);*/
    for (Entity e : entities) {
      /*printf("Saved entity %zu \n", e);*/
    }
    for (i32 i = 0; i < entities.size(); i++) {
      if (entities[i] == entity) {
        return i;
      }
    }
    return -1;
  }

  std::vector<C> components;
  std::vector<Entity> entities;
};

class ECS {
public:
  static ECS *get();

  template <typename C> bool hasComponent(Entity entity) {
    if (ComponentPool<C> *pool = getComponentPool<C>()) {
      /*printf("%b \n", pool->hasEntity(entity));*/
      return pool->hasEntity(entity);
    }
    return false;
  }

  template <typename... Cs> bool hasAllComponents(Entity entity) {
    return (hasComponent<Cs>(entity) && ...);
  }

  template <typename C> void registerComponent() {
    if (ComponentPool<C> *pool = getComponentPool<C>()) {
      return;
    }

    component_pools.push_back(std::make_unique<ComponentPool<C>>());
  }

  template <typename C> void addEntityComponent(Entity entity, C component) {
    if (ComponentPool<C> *pool = getComponentPool<C>()) {
      pool->addEntityComponent(entity, std::move(component));
      /*printf("Added component to entity size is %zu\n", pool->size());*/
    }
    update_queries_flag = true;
  }

  template <typename C> void removeEntityComponent(Entity entity) {
    if (ComponentPool<C> *pool = getComponentPool<C>()) {
      pool->removeEntityComponent(entity);
    }
  }

  void queueEntityDelete(Entity entity);

  Entity createEntity();

  void update();

  template <typename... Cs> class ComponentTuple {
  public:
    ComponentTuple(Cs *...cs) { tuple = std::make_tuple(cs...); }

    template <std::size_t Index>
    std::tuple_element_t<Index, std::tuple<Cs *...>> get() {
      return std::get<Index>(tuple);
    }

  private:
    std::tuple<Cs *...> tuple;
  };

  class Query {
  public:
    virtual ~Query() {};
    virtual void init() = 0;
  };

  template <typename... Cs> class ComponentQuery : public Query {
  public:
    ComponentQuery() { init(); }

    void init() override {
      components = ECS::get()->queryComponents<Cs...>();
      entities = ECS::get()->queryEntities<Cs...>();
    }

    std::vector<ComponentTuple<Cs...>> components;
    std::vector<Entity> entities;
  };

  template <typename... Qs> void addSystem(void (*cb_ptr)(Qs...)) {
    systems.push_back(
        std::make_unique<System<Qs...>>(std::function(cb_ptr)));
  }

  template <typename R> void addResource(R resource) {
    if (getResource<R>() != nullptr) {
      return;
    }
    resources.push_back(std::make_unique<Resource<R>>(std::move(resource)));
  }

  template <typename R> class ResourceQuery : public Query {

  public:
    ResourceQuery() { init(); }

    void init() override { resource = ECS::get()->getResource<R>()->get(); }

    R *get() { return resource; }

  private:
    R *resource;
  };

  void postUpdate();

  void runStartupSystems();

  class IModule {
  public:
    virtual ~IModule() {};
  };

  template <class M, typename... Args> void enableModule(Args... args) {
    if (!isModuleEnabled<M>()) {
      enabled_modules.push_back(std::make_unique<M>(args...));
    }
  }

  template <class M> bool isModuleEnabled() {
    for (std::unique_ptr<IModule> &mod : enabled_modules) {
      if (M *_ = dynamic_cast<M *>(mod.get())) {
        return true;
      }
    }
    return false;
  }

private:
  ECS() {};
  ~ECS() {};

  void updateQueryCache() {
    for (std::unique_ptr<Query> &query : query_cache) {
      query->init();
    }
  }

  template <typename... Qs> using SystemCallback = std::function<void(Qs...)>;

  class ISystem {
  public:
    virtual ~ISystem() {};
    virtual void call() = 0;
  };

  template <class Qs> Qs getQuery() {
    for (std::unique_ptr<Query> &query_ptr : query_cache) {
      if (Qs *qs = dynamic_cast<Qs *>(query_ptr.get())) {
        return *qs;
      }
    }
    query_cache.push_back(std::make_unique<Qs>());
    return Qs();
  }

  template <typename... Qs> class System : public ISystem {
  public:
    System(SystemCallback<Qs...> callback) { this->callback = callback; }

    void call() override { callback(ECS::get()->getQuery<Qs>()...); }

  private:
    SystemCallback<Qs...> callback;
  };

  class IResource {
  public:
    virtual ~IResource() {};
  };

  template <typename R> class Resource : public IResource {
  public:
    Resource(R resource) { this->resource = std::move(resource); }

    R *get() { return &resource; }

  private:
    R resource;
  };

  template <typename R> Resource<R> *getResource() {
    for (std::unique_ptr<IResource> &r_ptr : resources) {
      if (Resource<R> *resource = dynamic_cast<Resource<R> *>(r_ptr.get())) {
        return resource;
      }
    }
    return nullptr;
  }

  template <typename... Cs>
  std::vector<ComponentTuple<Cs...>> queryComponents() {
    std::vector<ComponentTuple<Cs...>> result_vec = {};
    /*printf("Running query components\n");*/
    for (Entity entity = 0; entity <= ECS::entity_counter; entity++) {
      if (hasAllComponents<Cs...>(entity)) {
        /*printf("Found matching entity\n");*/
        ComponentTuple<Cs...> tuple = ComponentTuple(
            getComponentPool<Cs>()->getEntityComponent(entity)...);
        result_vec.push_back(tuple);
      }
    }

    return result_vec;
  }

  template <typename... Cs> std::vector<Entity> queryEntities() {
    std::vector<Entity> result_vec = {};

    for (Entity entity = 0; entity <= ECS::entity_counter; entity++) {
      if (hasAllComponents<Cs...>(entity)) {
        result_vec.push_back(entity);
      }
    }
    return result_vec;
  }

  template <typename C> ComponentPool<C> *getComponentPool() {
    for (std::unique_ptr<IComponentPool> &pool_ptr : component_pools) {
      if (ComponentPool<C> *pool =
              dynamic_cast<ComponentPool<C> *>(pool_ptr.get())) {
        return pool;
      }
    }
    return nullptr;
  }

  void removeEntity(Entity entity);

  std::vector<Entity> entity_deletion_queue;
  Entity entity_counter;
  std::vector<Entity> unused_entity_ids;
  std::vector<std::unique_ptr<IComponentPool>> component_pools;
  std::vector<std::unique_ptr<ISystem>> systems;
  std::vector<std::unique_ptr<IResource>> resources;
  std::vector<std::unique_ptr<IModule>> enabled_modules;
  std::vector<std::unique_ptr<Query>> query_cache;
  bool update_queries_flag = false;

  static ECS instance;
};

ECS *getECS();
} // namespace Zenith
