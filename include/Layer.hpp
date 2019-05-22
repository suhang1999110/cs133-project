#ifndef CS133_LAYER_HPP
#define CS133_LAYER_HPP

#include <Eigen/Core>
#include <vector>
#include <cstddef>

// layer base class
class Layer{
 public:
  Layer();
  virtual ~Layer();
  // initialize the parameters (including input size, output size, number of nodes etc.)
  virtual void init() = 0;
  // compute the output of this layer
  virtual void forward() = 0;
  // get the size of input
  int in_size() const;
  // get the size of output
  int out_size() const;

 private:
  size_t node_num;
  // number of input units of this hidden layers. Equal to the number of output units of the previous layer.
  const int in_size;
  // number of output units of this hidden layers. Equal to the number of input units of the next layer.
  const int out_size;
};

#endif