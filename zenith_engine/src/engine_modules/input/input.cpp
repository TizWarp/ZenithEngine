#include "input.hpp"

namespace Zenith {

void updateInputSys(ECS::ResourceQuery<Keys> keys_querry);

InputModule::InputModule() {

  ECS *ecs = ECS::get();

  ecs->addResource(Keys());

  ecs->addSystem(127, updateInputSys);
}

void Keys::update() {
  for (auto &[key, value] : is_just_released) {
    value = false;
  }
  for (auto &[key, value] : is_just_pressed) {
    value = false;
  }
}

void updateInputSys(ECS::ResourceQuery<Keys> keys_querry) {
  Keys *keys = keys_querry.get();
  keys->update();
}
void Keys::keyDown(std::string key) {
  is_pressed[key] = true;
  is_just_pressed[key] = true;
}


void Keys::keyUp(std::string key){
  is_pressed[key] = false;
  is_just_released[key] = true;
}

bool Keys::isKeyDown(std::string key){
  if (is_pressed.find(key) != is_pressed.end()){
    return is_pressed[key];
  }
  return false;
}

bool Keys::isKeyJustPressed(std::string key){
  if (is_just_pressed.find(key) != is_just_pressed.end()){
    return is_just_pressed[key];
  }
  return false;
}


bool Keys::isKeyJustReleased(std::string key){
  if (is_just_released.find(key) != is_just_released.end()){
    return is_just_released[key];
  }
  return false;
}

} // namespace Zenith
