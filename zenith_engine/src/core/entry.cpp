#include "entry.hpp"
#include "ecs.hpp"
#include "../zenith.hpp"
#include "SDL3/SDL.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <cstdio>
#include <SDL3_image/SDL_image.h>


using namespace Zenith;

bool running = true;



void gamestateSys(ECS::ResourceQuery<GameState> querry){
  GameState *game_state = querry.get();
  running = game_state->running;
}



int main(){


  Zenith::z_main();

  ECS::get()->addResource(GameState{true});
  ECS::get()->addSystem(127, gamestateSys);


  unsigned int i = 0;

  while(running){
    i += 1;
    ECS::get()->update();
    /*printf("Frame %d\n", i);*/
  }


}
