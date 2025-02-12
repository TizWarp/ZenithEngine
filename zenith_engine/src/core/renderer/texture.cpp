#include "texture.hpp"
#include <cstdio>
#include <stb_image.h>
#include <GL/glew.h>
#include "../defines.hpp"
#include "spdlog/spdlog.h"

namespace Zenith{
  Texture2D::Texture2D(const char* path){
    int nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
   
    printf("test\n");

    if(data){
      glGenTextures(1, &ID);
     
      glBindTexture(GL_TEXTURE_2D, ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      printf("done\n");
      
    } else {
      Logger::error("Failed to load texture at path");
    }

    /*glBindTexture(GL_TEXTURE_2D, 0);*/
    stbi_image_free(data);
  }



  Texture2D::~Texture2D(){
    /*glDeleteTextures(1, &ID);*/
  }


}
