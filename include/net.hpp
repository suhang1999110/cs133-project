// implement of Net class
#ifndef CS133_NET_IMPL_HPP
#define CS133_NET_IMPL_HPP

#include "Layer.hpp"
#include "layers/Convolutional.hpp"
#include "layers/Dense.hpp"
#include "layers/MaxPooling.hpp"
#include "../third_party/toy_json/include/toy_json.hpp" // json parser
#include <Eigen/Core>
#include <fstream>
#include <string>
#include <cassert>      // assert()

Net::Net(){}

Net::~Net(){
  // release all layer pointer
  for(size_t i = 0;i < num_layers();++i){
    delete m_layers[i];
  }
}

void
Net::init(const std::string & model_path, const std::string & weights_path){
  load_model(model_path);
  load_weights(weights_path);
}

void
Net::forward(const Eigen::MatrixXd & input){
  // pass input to the first layer
  m_layers[0]->forward(input);
  // use the previous layer's output as next layer's input
  for(int i = 1;i < num_layers();++i){
    m_layers[i]->forward(m_layers[i-1]->output());
  }
}

void
Net::add_layer(Layer * layer){
  m_layers.push_back(layer);
}

void
Net::load_model(const std::string & path){
  using toy_json::Json;
  using toy_json::JsonNode;

  std::unique_ptr<JsonNode> jsonPtr = Json::parse(path);
  assert(jsonPtr);
  // layer message in json
  auto jsonLayers = (*jsonPtr)["config"]["layers"];
  for(auto i = 0;i < jsonLayers.size();++i){
    Layer * layer = nullptr;

    switch(jsonLayers[i]["class_name"].get_string().c_str()){
      case "Conv2D":
        layer = new Conv();
        layer->init(jsonLayers[i]["config"]["batch_input_shape"][1].get_number(),
                    jsonLayers[i]["config"]["batch_input_shape"][2].get_number(),
                    jsonLayers[i]["config"]["filters"].get_number(),
                    jsonLayers[i]["config"]["kernel_size"][0].get_number(),
                    jsonLayers[i]["config"]["kernel_size"][1].get_number(),
                    jsonLayers[i]["config"]["activation"].get_string(),
                    jsonLayers[i]["config"]["name"].get_string());
        add_layer(layer);
        break;

      case "MaxPooling2D":
        layer = new Pooling();
        layer->init(jsonLayers[i]["config"]["pool_size"][0].get_number(),
                    jsonLayers[i]["config"]["pool_size"][1].get_number(),
                    jsonLayers[i]["config"]["padding"][0].get_number(),
                    jsonLayers[i]["config"]["padding"][1].get_number(),
                    jsonLayers[i]["config"]["name"].get_string());
        add_layer(layer);
        break;

      case "Dense":
        layer = new Dense();
        layer->init(jsonLayers[i]["config"]["units"].get_number(), 
                    jsonLayers[i]["config"]["activation"].get_string(),
                    jsonLayers[i]["config"]["name"].get_string());
        add_layer(layer);
        break;

      // optional
      // case "Flatten":
      //   layer = new Flatten();
      //   layer->init(jsonLayers[i]["config"]["name"].get_string());
      //   add_layer(layer);
      //   break;
    }
  }
}

void
Net::load_weights(const std::string & path){
  using toy_json::Json;
  using toy_json::JsonNode;

  std::unique_ptr<JsonNode> jsonPtr = Json::parse(path);
  assert(jsonPtr);
  for(auto it = m_layers.begin();it != m_layers.end();++it){
    auto layerWeights = (*jsonPtr)[(*it)->get_name()]["weights"];
    auto layerBias = (*jsonPtr)[(*it)->get_name()]["bias"];
    switch((*it)->get_type()){
      case Layer::Conv:

        break;
      case Layer::Pooling:
        
        break;
      case Layer::Dense:{
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
      // case Layer::Flatten:
      //   break;
    }
  }
}

Eigen::MatrixXd
Net::output() const{
  return m_outputLayer.output();
}

size_t
Net::num_layers() const{
  return m_layers.size();
}

#endif // CS133_NET_IMPL_HPP