// implement of Net class
#ifndef CS133_NET_IMPL_HPP
#define CS133_NET_IMPL_HPP

#include "Layer.hpp"
#include "layers/Convolutional.hpp"
#include "layers/Dense.hpp"
#include "layers/MaxPooling.hpp"
#include "layers/Flatten.hpp"
#include "activation/ReLU.hpp"
#include "activation/Sigmoid.hpp"
#include "activation/Softmax.hpp"
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

Eigen::MatrixXd
Net::forward(const Eigen::MatrixXd & input){
  // pass input to the first layer
  m_layers[0]->forward(input);

  // use the previous layer's output as next layer's input
  for(int i = 1;i < num_layers();++i){
    m_layers[i]->forward(m_layers[i-1]->output());
  }
  
  // store the output of the last layer
  m_output = m_layers[num_layers() - 1]->output()[0];
  return m_output;
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

  // set input size of the net
  int cur_input_row = jsonLayers[0]["config"]["batch_input_shape"][1].get_number();
  int cur_input_col = jsonLayers[0]["config"]["batch_input_shape"][2].get_number();
  int cur_input_num = 1;

  // parse each layer message in json
  for(auto i = 0;i < jsonLayers.size();++i){
    Layer * layer = nullptr;

    // determine layer type
    switch(jsonLayers[i]["class_name"].get_string().c_str()){
      case "Conv2D":
        layer = new Convolutional();
        layer->init(cur_input_num,
                    cur_input_row,
                    cur_input_col,
                    jsonLayers[i]["config"]["filters"].get_number(),
                    jsonLayers[i]["config"]["kernel_size"][0].get_number(),
                    jsonLayers[i]["config"]["kernel_size"][1].get_number(),
                    jsonLayers[i]["config"]["strides"][0].get_number(),
                    jsonLayers[i]["config"]["strides"][1].get_number(),
                    jsonLayers[i]["config"]["padding"].get_string(),
                    jsonLayers[i]["config"]["name"].get_string());
        // update input size
        cur_input_num = layer->out_size();
        cur_input_row = layer->output_row();
        cur_input_col = layer->output_col();

        add_layer(layer);

        // create activation layer
        Layer * act;
        switch(jsonLayers[i]["config"]["activation"].get_string().c_str()){
          case "relu":
            act = new Relu();
            break;
          case "softmax":
            act = new Softmax();
            break;
          case "sigmoid":
            act = new Sigmoid();
            break;
        }
        // initialize activation layer and add it to the net
        act.init();
        add_layer(act);

        break;

      case "MaxPooling2D":
        layer = new MaxPooling();
        layer->init(cur_input_num,
                    cur_input_row,
                    cur_input_col,
                    jsonLayers[i]["config"]["pool_size"][0].get_number(),
                    jsonLayers[i]["config"]["pool_size"][1].get_number(),
                    jsonLayers[i]["config"]["padding"].get_string(),
                    jsonLayers[i]["config"]["name"].get_string());
        // update input size
        cur_input_num = layer->out_size();
        cur_input_row = layer->output_row();
        cur_input_col = layer->output_col();
        
        add_layer(layer);
        break;

      case "Dense":
        layer = new Dense();
        layer->init(cur_input_num,
                    cur_input_row,
                    cur_input_col,
                    jsonLayers[i]["config"]["units"].get_number(), 
                    jsonLayers[i]["config"]["name"].get_string());
        // update input size
        cur_input_num = layer->out_size();
        cur_input_row = layer->output_row();
        cur_input_col = layer->output_col();

        add_layer(layer);

        // create activation layer
        Layer * act;
        switch(jsonLayers[i]["config"]["activation"].get_string().c_str()){
          case "relu":
            act = new Relu();
            break;
          case "softmax":
            act = new Softmax();
            break;
          case "sigmoid":
            act = new Sigmoid();
            break;
        }
        // initialize activation layer and add it to the net
        act.init();
        add_layer(act);

        break;

      case "Flatten":
        layer = new Flatten();
        layer->init(cur_input_num,
                    cur_input_row,
                    cur_input_col,
                    jsonLayers[i]["config"]["name"].get_string());
        // update input size
        cur_input_num = layer->out_size();
        cur_input_row = layer->output_row();
        cur_input_col = layer->output_col();
        
        add_layer(layer);
        break;
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
    // get weights and bias array in json
    auto layerWeights = (*jsonPtr)[(*it)->get_name()]["weights"];
    auto layerBias = (*jsonPtr)[(*it)->get_name()]["bias"];
    
    // determine layer type
    switch((*it)->get_type()){
      case Layer::Conv:{
        // parameters to initialize
        std::vector<std::vector<Eigen::MatrixXd>> kernel((*it)->node_num(), std::vector<Eigen::MatrixXd>((*it)->in_size(), Eigen::MatrixXd((*it)->kernel_row(), (*it)->kernel_row())));
        std::vector<double> bias((*it)->node_num());

        // construct kernel from json
        for(int i = 0;i < (*it)->node_num();++i){
          for(int j = 0;j < (*it)->node_num();++j){
            for(int k = 0;k < (*it)->kernel_row();++k){
              for(int l = 0;l < (*it)->kernel_col();++l){
                kernel[i][j](k,l) = layerWeights[i][j][k][l].get_number();
              }
            }
          }
        }

        // construct bias from json
        for(int i = 0;i < (*it)->node_num();++i){
          bias[i] = layerBias[i].get_number();
        }

        break;
      }
      case Layer::Dense:{
        // parameters to initialize
        Eigen::MatrixXd weights((*it)->node_num(), (*it)->input_row());
        Eigen::MatrixXd bias((*it)->node_num(), 1);
        
        for(size_t i = 0;i < (*it)->node_num();++i){
          // set weights
          for(size_t j = 0;j < (*it)->input_row();++j){
            weights(i,j) = layerWeights[i][j].get_number();
          }
          // set bias
          bias(i) = layerBias[i].get_number();
        }
        (*it)->init(weights, bias);
        break;
      }
    }
  }
}

Eigen::MatrixXd
Net::output() const{
  return m_output;
}

size_t
Net::num_layers() const{
  return m_layers.size();
}

#endif // CS133_NET_IMPL_HPP