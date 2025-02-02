#include "renderer.hpp"
#include "../defines.hpp"
#include "GL/glew.h"
#include "shader.hpp"
#include "spdlog/fmt/bundled/base.h"
#include "spdlog/spdlog.h"
#include <cstdio>
#include <iterator>
namespace Zenith {

namespace Renderer {

float vertices[] = {
    0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
};

unsigned int VBO, VAO;

Shader shader;

bool initRenderer() {
  glewExperimental = true;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    Logger::error("Failed to start glew");
    return false;
  }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  shader = Shader("/home/tizwarp/Projects/zenithEngine/zenith_engine/assets/"
                  "shaders/basic.vs",
                  "/home/tizwarp/Projects/zenithEngine/zenith_engine/assets/"
                  "shaders/basic.fs");

  shader.use();

  return true;
}

void beginFrame() {
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawFrame() { glDrawArrays(GL_TRIANGLES, 0, 3); }


} // namespace Renderer
} // namespace Zenith
