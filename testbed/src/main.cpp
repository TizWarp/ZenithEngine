#include <core/ecs.hpp>
#include <core/entry.hpp>
#include <cstdio>
#include <zenith.hpp>

using namespace Zenith;


struct Position{
  int x;
  int y;
};

void test_sys(ECS::ComponentQuery<Position> query){
  Logger::info("TEST");
}


void setupGame(Zenith::GameInfo &game_info) {
  game_info.game_name = "Testbed";
  game_info.clear_color = Math::vec4(0.5f, 0.5f, 0.5f, 1.0f);


  ECS::registerComponent<Position>();
  ECS::addSystem(test_sys);

}
