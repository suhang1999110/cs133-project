#ifndef CS133_NET_HPP
#define CS133_NET_HPP

#include "Layer.hpp"
#include <list>

// Net consists of several layers
class Net{
 public:
  Net();
  ~Net();
  // initialzie all the hidden layers
  void init();
  // compute the ouput of the entire network
  void forward();
  // add a layer to the network
  void add_layer();
  // return the number of layers
  size_t num_layers();

 private:
  std::list<Layer> layers;
}

#endif // CS133_NET_HPP