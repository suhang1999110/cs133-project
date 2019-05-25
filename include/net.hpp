// implement of Net class
#ifndef CS133_NET_IMPL_HPP
#define CS133_NET_IMPL_HPP

#include "Layer.hpp"
#include "layers/Convolutional.hpp"
#include "layers/Dense.hpp"
#include "layers/MaxPooling.hpp"
#include "toy_json.hpp" // json parser
#include <Eigen/Core>
#include <fstream>
#include <string>
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
  auto jsonLayers = (*jsonPtr)["config"]["layers"];
  for(auto i = 0;i < jsonLayers.size();++i){
    Layer * layer = nullptr;

    switch(jsonLayers[i]["class_name"].get_string()){
      case std::string("Conv2D"):
        layer = new Conv();
        layer->init(jsonLayers[i]["config"]["batch_input_shape"][1].get_number(),
                    jsonLayers[i]["config"]["batch_input_shape"][2].get_number(),
                    jsonLayers[i]["config"]["filters"].get_number(),
                    jsonLayers[i]["config"][0].get_number(),
                    jsonLayers[i]["config"][1].get_number(),
                    jsonLayers[i]["config"]["activation"].get_string(),
                    jsonLayers[i]["config"]["name"].get_string());
        add_layer(layer);
        break;

      case std::string("MaxPooling2D"):
        layer = new Pooling();
        layer->init(jsonLayers[i]["config"]["pool_size"][0].get_number(),
                    jsonLayers[i]["config"]["pool_size"][1].get_number(),
                    jsonLayers[i]["config"]["padding"][0].get_number(),
                    jsonLayers[i]["config"]["padding"][1].get_number(),
                    jsonLayers[i]["config"]["name"].get_string());
        add_layer(layer);
        break;

      case std::string("Dense"):
        layer = new Dense();
        layer->init(jsonLayers[i]["config"]["units"].get_number(), 
                    jsonLayers[i]["config"]["activation"].get_string(),
                    jsonLayers[i]["config"]["name"].get_string());
        add_layer(layer);
        break;

      // optional
      case std::string("Flatten"):
        layer = new Flatten();
        layer->init(jsonLayers[i]["config"]["name"].get_string());
        add_layer(layer);
        break;
    }
  }
}

void
load_weights(const std::string & path){
  using toy_json::Json;
  using toy_json::JsonNode;

  std::unique_ptr<JsonNode> jsonPtr = Json::parse(path);
  assert(jsonPtr);
  for(auto it = layers.begin();it != layers.end();++it){
    auto layerWeights = (*jsonPtr)[(*it)->name]["weights"];
    auto layerBias = (*jsonPtr)[((*it)->name)]["bias"];
    switch((*it)->type){
      case std::string("Conv"):

        break;
      case std::string("Pooling"):
        
        break;
      case std::string("Dense"):{
        Eigen::MatrixXd weights((*it)->num_node(), (*it)->node_size());
        Eigen::VectorXd bias((*it)->num_node());
        for(size_t i = 0;i < (*it)->num_node();++i){
          // set weights
          for(size_t j = 0;j < (*it)->node_size();++j){
            weights(i,j) = layerWeights[i][j].get_number();
          }
          // set bias
          bias(i) = layerBias[i].get_number();
        }
        (*it)->init(weights, bias);
        break;
      }
      // optional
      case std::string("Flatten"):
        
        break;
    }
  }
}



#endif // CS133_NET_IMPL_HPP