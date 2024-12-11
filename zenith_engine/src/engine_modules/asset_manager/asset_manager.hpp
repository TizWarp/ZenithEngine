#pragma once
#include "../../core/ecs.hpp"
#include <map>
#include <string>
#include <vector>

namespace Zenith {

  template<typename T>
  class AssetManager{
    public:
      
      bool loadResource(std::string path, std::string name);
      T* getResource(std::string name);
      bool deleteResource(std::string name);

      std::string getError();


    protected:
      std::map<std::string, T> loaded_resources;
      std::string error_str;


  };


  class Image{

  };


  class AssetManagerModule : public ECS::IModule{
    public:
      AssetManagerModule();
  };
  
}
