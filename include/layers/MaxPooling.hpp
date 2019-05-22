// TO-DO
// The max pooling layer
// a child class of layer
#ifndef CS133_LAYER_DENSE_HPP
#define CS133_LAYER_DENSE_HPP

#include <Eigen/Core>
#include <vector>

class Pooling : class Layer
{
 public:
  Pooling();
  ~Pooling();
  void init();
  void forward();
 
 private:
  size_t node_num;
};

#endif