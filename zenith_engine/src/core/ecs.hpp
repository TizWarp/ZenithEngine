#pragma once
#include "defines.hpp"
#include "../zenith.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <fmt/base.h>
#include <functional>
#include <spdlog/spdlog.h>
#include <sys/types.h>
#include <tuple>
#include <type_traits>
#include <vector>
namespace Zenith::ECS {

typedef u64 Entity;

class IComponentPool {
public:
  virtual ~IComponentPool() {};
  virtual void removeEntityComponent(Entity entity) = 0;
};

template <typename T> class ComponentPool : public IComponentPool {
public:


  ComponentPool(){
    components = {};
    entities = {};
  }

  void removeEntityComponent(Entity entity) override{
    u64 index = getEntityIndex(entity);
    if (index == -1) {
      Logger::warn("Tried to remove component from entity that doesn't have "
                   "that component");
      return;
    }

    entities[index] = entities[entities.size() - 1];
    entities.pop_back();

    components[index] = components[components.size() - 1];
    components.pop_back();
  }

  bool hasEntity(Entity entity) { return getEntityIndex(entity) != -1; }

  void addEntityComponent(Entity entity, T component) {
    if (getEntityIndex(entity) != -1) {
      Logger::warn(
          "Tried add component to entity that already has that component");
      return;
    }

    Logger::info("Adding entity");
    entities.push_back(entity);
    components.push_back(component);
    Logger::info("Added entity");
  }

  T& getEntityComponent(Entity entity){
    i64 index = getEntityIndex(entity);
    return components[index];
  }

private:
  i64 getEntityIndex(Entity entity) {
    for (i64 i = 0; i < entities.size(); i++) {
      if (entities[i] == entity) {
        return i;
      }
    }

    return -1;
  }

  std::vector<T> components;
  std::vector<Entity> entities;
};

void queueDelete(Entity entity);
Entity createEntity();
extern std::vector<Entity> entity_ids;
extern std::vector<IComponentPool *> component_pools;


template <typename C> ComponentPool<C> *getComponentPool() {
  for (IComponentPool *pool_ptr : component_pools) {
    if (ComponentPool<C>* pool = dynamic_cast<ComponentPool<C> *>(pool_ptr)) {
      return pool;
    }
  }
  return nullptr;
}

template <typename C> bool hasComponent(Entity entity) {
  ComponentPool<C> *pool = getComponentPool<C>();

  if (pool == nullptr) {
    return false;
  }

  return pool->hasEntity(entity);
}

template <typename... Cs> bool hasAll(Entity entity) {
  return (hasComponent<Cs>(entity) && ...);
}




template<typename C>
void registerComponent(){
  component_pools.push_back(new ComponentPool<C>());
}

template<typename C>
void addEntityComponent(Entity entity, C component){
  ComponentPool<C>* pool = getComponentPool<C>();

  if (pool == nullptr){
    return;
  }

  pool->addEntityComponent(entity, component);
}


template<typename C>
bool removeEntityComponent(Entity entity){
  ComponentPool<C>* pool = getComponentPool<C>();
  if (pool == nullptr){
    return false;
  }

  pool->removeEntityComponent(entity);
}





template <typename... Cs> class QueryTuple {
public:
  QueryTuple(Cs &...cs) { this->tuple = std::make_tuple<Cs *...>(&cs...); }

  template <std::size_t Index>
  std::tuple_element_t<Index, std::tuple<Cs *...>> get() {
    return std::get<Index>(tuple);
  }

private:
  std::tuple<Cs *...> tuple;
};

template <typename... Cs> std::vector<QueryTuple<Cs...>> queryComponents() {
  std::vector<QueryTuple<Cs...>> result_vec = {};

  for (Entity entity : entity_ids){
    if (hasAll<Cs...>(entity)){
      QueryTuple<Cs...> tuple = QueryTuple(getComponentPool<Cs>()->getEntityComponent(entity)...);
      result_vec.push_back(tuple);
    }
  }

  return result_vec;
}

template <typename... Cs> std::vector<Entity> queryEntities() {
  std::vector<Entity> result_vec = {};

  for (Entity entity : entity_ids){
    if (hasAll<Cs...>(entity)){
      result_vec.push_back(entity);
    }
  }
  return result_vec;
}


template <typename... Cs> class ComponentQuery{
public:

  ComponentQuery(){
    components = queryComponents<Cs...>();
    entities = queryEntities<Cs...>();
  }

  std::vector<QueryTuple<Cs...>>& getComponents() { return components; }

  std::vector<Entity>& getEntities() { return entities; }

  size_t size() { return components.size(); }

  QueryTuple<Cs...> operator[](std::size_t index) { return components[index]; }

private:
  std::vector<QueryTuple<Cs...>> components;
  std::vector<Entity> entities;
};


template<class... Qs>
using SystemCallback = std::function<void(Qs...)>;

class ISystem{
  public:
  virtual ~ISystem() {};
  virtual void call() = 0;
};


extern std::vector<ISystem*> systems;


template<class... Qs>
class System : public ISystem{
  public:


    System(SystemCallback<Qs...> callback){
      this->callback = callback;
    }

    void call() override{
      callback(constructQuery<Qs>()...);
    }


  private:

    template<class Q>
    Q constructQuery(){
      return Q();
    }

    SystemCallback<Qs...> callback;
};


template<class... Qs>
void addSystem(SystemCallback<Qs...> callback){
  systems.push_back(new System<Qs...>(callback));
}


class IResource{
  public:
  virtual ~IResource() {};
};


template<typename R>
class Resource : public IResource{
  public:
    Resource(R resource){
      this->resource = resource;
    }

    R& get(){
      return resource;
    }

  private:

    R resource;

};

extern std::vector<IResource*> resources;

template<typename R>
void addResource(R resource){
  resources.push_back(new Resource<R>(resource));
}

template<typename R>
Resource<R>* getResource(){
  for (IResource* r_ptr : resources){
    if (Resource<R>* resource = dynamic_cast<Resource<R>*>(r_ptr) ){
      return resource;
    }
  }
  return nullptr;
}


template<typename R>
class ResourceQuery{
  public:
    ResourceQuery(){
      resource = getResource<R>();
    }


    R& get(){
      return resource->get();
    }

  private:

    Resource<R>* resource;
};


template<class... Qs>
using SystemPtr = void(*)(Qs...);

template<class... Qs>
void addSystem(SystemPtr<Qs...> ptr){
  addSystem(std::function(ptr));
}

void ecsUpdate();

} // namespace Zenith::ECS
