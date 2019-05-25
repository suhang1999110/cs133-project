// TO-DO
// The fully connected layer
// a child class of layer
#ifndef CS133_LAYER_DENSE_HPP
#define CS133_LAYER_DENSE_HPP

#include <Eigen/Core>
#include <vector>
#include "Layer.hpp"

class Dense : public Layer{
 public:
  Dense();
  ~Dense();
  void init();
  void forward();
  
 private:
  size_t node_num;
};

#endif