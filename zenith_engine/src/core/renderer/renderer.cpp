#include "renderer.hpp"
#include "../defines.hpp"
#include "../ecs.hpp"
#include "GL/glew.h"
#include "shader.hpp"
#include "spdlog/fmt/bundled/base.h"
#include "spdlog/spdlog.h"
#include "sprite2d.hpp"
#include "texture.hpp"
#include <cstdio>
#include <iomanip>
#include "../ecs.hpp"
#include "../window.hpp"
#include "../../ecs_modules/camera.hpp"
namespace Zenith {
#include "../../zenith.hpp"
namespace Renderer {

typedef vec2 Position;

void setupSpriteData();

const float sprite_vertices[] = {
  -0.75f, 0.75f, 0.0f, 1.0f, // 0
  -0.75f, -0.75f, 0.0f, 0.0f, // 1
  0.75f, 0.75f, 1.0f, 1.0f, // 2
  0.75f, -0.75f, 1.0f, 0.0f, // 3
};

const unsigned int sprite_indices[] = {
  0, 1, 3,
  0, 2, 3,
};

unsigned int SpriteVBO, SpriteVAO, SpriteEBO;

Shader spriteShader;

bool initRenderer() {
  glewExperimental = true;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    Logger::error("Failed to start glew");
    return false;
  }


  ECS::get()->registerComponent<Texture2D>();
  ECS::get()->registerComponent<Sprite2D>();

  setupSpriteData();

  return true;
}

void beginFrame() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int width, height;
  Window::getSize(&width, &height);
  glViewport(0, 0, width, height);
}


void drawFrame(ECS *ecs) {
  spriteShader.use();
  ECS::ComponentQuery<Sprite2D, Position> query = ecs->getQuery<ECS::ComponentQuery<Sprite2D, Position>>();
  ECS::ComponentQuery<Camera, Position> camQuerry = ecs->getQuery<ECS::ComponentQuery<Camera, Position>>();

  for (auto t : camQuerry.components){
    Camera *cam = t.get<0>();
    Position *pos = t.get<1>();
    spriteShader.setVec3("camera_position", vec3(pos->x, pos->y, cam->zoom));
  }


  for (auto t : query.components){
    Sprite2D *sprite = t.get<0>();
    Position *pos = t.get<1>();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite->texture);
    glBindVertexArray(SpriteVAO);
    spriteShader.setInt("texture1" , 0);
    spriteShader.setVec2("sprite_position", *pos);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}


void setupSpriteData(){

  spriteShader = Shader("./zenith_engine/assets/shaders/sprite2d.vs", "./zenith_engine/assets/shaders/sprite2d.fs");

  glGenVertexArrays(1, &SpriteVAO);
  glGenBuffers(1, &SpriteVBO);
  glGenBuffers(1, &SpriteEBO);

  glBindVertexArray(SpriteVAO);
  glBindBuffer(GL_ARRAY_BUFFER, SpriteVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SpriteEBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(sprite_vertices), sprite_vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite_indices), sprite_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
  glEnableVertexAttribArray(1);
}

} // namespace Renderer
} // namespace Zenith
