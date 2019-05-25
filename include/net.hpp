// implement of Net class
#ifndef CS133_NET_IMPL_HPP
#define CS133_NET_IMPL_HPP

#include "Layer.hpp"
#include <fstream>
#include <string>
#include "toy_json.hpp" // json parser
#include <cassert>      // assert)_

void
Net::init(const std::string & model_path, const std::string & weights_path){
  load_model(model_path);
  load_weights(weights_path);
}

void
load_model(const std::string & path){
  using toy_json::Json;
  using toy_json::JsonNode;

  std::unique_ptr<JsonNode> jsonPtr = Json::parse(path);
  assert(jsonPtr);
  // layer message in json
  auto layers = (*jsonPtr)["config"]["layers"];
  for(auto i = 0;i < layers.size();++i){
    Layer * layer = nullptr;

    switch(layers[i]["class_name"].get_string()){
      case std::string("Conv2D"):
        // TODO
        // layer = new ;
        break;
      case std::string("MaxPooling2D"):
        // layer = new 
        break;
      case std::string("Dense"):
        layer = new Dense();
        break;
      // optional
      case std::string("Flatten"):
        
        break;
    }
  }
}

void
load_weights(const std::string & path){

}

#endif // CS133_NET_IMPL_HPP