#ifndef CS133_NET_HPP
#define CS133_NET_HPP

#include "Layer.hpp"
#include <list>

class Net : class Layer{
 public:
  Net();
  ~Net();
  void init();
  void forward();
  void add_layer();
  size_t num_layers();

 private:
  std::list<Layer> layers;
}

#endif // CS133_NET_HPP