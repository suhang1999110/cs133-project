///@file Net.hpp
///@brief Interface of Net class

#ifndef CS133_NET_HPP
#define CS133_NET_HPP

#include "Layer.hpp"
#include "layers/Convolutional.hpp"
#include "layers/Dense.hpp"
#include "layers/MaxPooling.hpp"
#include "layers/Flatten.hpp"
#include "activation/ReLU.hpp"
#include "activation/Sigmoid.hpp"
#include "activation/Softmax.hpp"
#include "../third_party/rapidjson/document.h"
#include <vector>
#include <string>
#include <Eigen/Core>
#include <fstream>
#include <cassert>

///@brief Class of network, consists of several layers
class Net{
 public:
  /// default constructord
  Net();
  
  /// default deconstructor
  ~Net();
  
  /// initialzie all the hidden layers with given the path of model and weights
  /// JSON format by default
  /// a wrapper of load_model() and load_weights
  void init(const std::string & model_path, const std::string & weights_path);
  
  /// compute the ouput of the entire network
  /// return the output matrix
  Eigen::MatrixXd forward(const Eigen::MatrixXd & input);
  
  /// add a layer to the network
  void add_layer(Layer * layer);
  
  /// read model from given path
  void load_model(const std::string & path);
  
  /// read weights from given path
  void load_weights(const std::string & path);

  /// return output
  Eigen::MatrixXd output() const;

  /// return the number of layers
  size_t num_layers() const;
  

 private:
  /// all hidden layers
  std::vector<Layer*> m_layers;
  /// output
  Eigen::MatrixXd m_output;
};

#include "net_v2.hpp"

#endif // CS133_NET_HPP