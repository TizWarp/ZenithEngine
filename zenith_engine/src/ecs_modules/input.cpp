
#include "input.hpp"

namespace Zenith {

void Keys::keyUp(std::string key) {
  pressed[key] = false;
  just_released[key] = true;
  just_pressed[key] = false;
}

void Keys::keyDown(std::string key) {
  pressed[key] = true;
  just_pressed[key] = true;
  just_released[key] = false;
}

bool Keys::isKeyDown(std::string key) {
  if (pressed.find(key) != pressed.end()) {
    return pressed[key];
  }
  return false;
}

bool Keys::isKeyJustPressed(std::string key) {
  if (just_pressed.find(key) != just_pressed.end()) {
    return just_pressed[key];
  }
  return false;
}

bool Keys::isKeyJustReleased(std::string key) {
  if (just_released.find(key) != just_released.end()) {
    return just_released[key];
  }
  return false;
}

void Keys::update() {
  for (auto &[_, v] : just_pressed) {
    v = false;
  }
  for (auto &[_, v] : just_released) {
    v = false;
  }
}

} // namespace Zenith
