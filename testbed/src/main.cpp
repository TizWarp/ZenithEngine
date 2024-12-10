#include "core/entry.hpp"
#include "engine_modules/input/input.hpp"
#include "engine_modules/window/window.hpp"
#include <cstdio>
#include <fmt/base.h>
#include <zenith.hpp>
#include<core/ecs.hpp>


using namespace Zenith;


void Zenith::z_main(){

  ECS* ecs = ECS::get();



  ecs->enableModule<WindowModule>("TEST");

  /*ecs->addSystem(1, test_sys);*/

}
