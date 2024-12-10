#pragma once
#include "../../core/ecs.hpp"
#include <algorithm>
#include <map>
#include <string>

namespace Zenith {

class Keys;


class Keys {
public:
  void keyDown(std::string key);
  void keyUp(std::string key);

  bool isKeyDown(std::string key);
  bool isKeyJustPressed(std::string key);
  bool isKeyJustReleased(std::string key);

  void update();

private:
  std::map<std::string, bool> is_pressed;
  std::map<std::string, bool> is_just_pressed;
  std::map<std::string, bool> is_just_released;
};

class InputModule : public ECS::IModule {
public:
  InputModule();
};

} // namespace Zenith
