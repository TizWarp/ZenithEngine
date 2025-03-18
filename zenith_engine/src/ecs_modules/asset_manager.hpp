#pragma once
#include "../core/defines.hpp"
#include <cassert>
#include <map>
#include <string>


namespace Zenith{
  template <class A>
  class AssetManager{

    A* getAsset(std::string asset){
      if (assets.find(asset) != assets.end()){
        return &assets[asset];
      }
      return nullptr;
    }

    A* createAsset e

    

    private:
      std::map<std::string, A> assets;
  };
}
