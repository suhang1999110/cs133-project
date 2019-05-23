#ifndef CS133_NET_HPP
#define CS133_NET_HPP

#include "Layer.hpp"
#include <vector>
#include <string>
#include <Eigen/Core>

// Net consists of several layers
class Net{
 public:
  // default constructord
  Net();
  
  // default deconstructor
  ~Net();
  
  // initialzie all the hidden layers with given the path of model and weights
  // a wrapper of load_model() and load_weights
  void init(const std::string & model_path, const std::string & weights_path, const std::string & name = "Net");
  
  // compute the ouput of the entire network
  void forward();
  
  // add a layer to the network
  void add_layer();
  
  // read model from given path
  void load_model(const std::string & path);
  
  // read weights from given path
  void load_weights(const std::string & path);

  // set input layer with given matrix
  void set_input(const Eigen::MatrixXd & input);

  // return output
  Eigen::MatrixXd output() const;

  // return output
  Eigen::MatrixXd input() const;
  
  // return the number of layers
  size_t num_layers() const;
  
  // return the name of this net
  const std::string & get_name() const;

 private:
  // all hidden layers
  std::vector<Layer> layers;
  // input layer
  Layer inputLayer;
  // output layer
  Layer outputLayer;
  // the name of this net (default "Net")
  std::string name;
}

#endif // CS133_NET_HPP