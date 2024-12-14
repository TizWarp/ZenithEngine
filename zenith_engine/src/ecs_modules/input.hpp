#pragma once
#include "../core/ecs.hpp"
#include <map>
#include <string>

namespace Zenith {

class Keys {
public:



  void keyDown(std::string key);
  void keyUp(std::string key);


  bool isKeyDown(std::string key);
  bool isKeyJustPressed(std::string key);
  bool isKeyJustReleased(std::string key);


  void update();

private:
  std::map<std::string, bool> pressed;
  std::map<std::string, bool> just_pressed;
  std::map<std::string, bool> just_released;
};

} // namespace Zenith
