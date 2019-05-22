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
  virtual void init() = 0;
  // froward propagation
  virtual void forward() = 0;
  // in_size getter
  int in_size() const;
  // out_size getter
  int out_size() const;

 private:
  size_t node_num;
  Eigen::MatrixXd nodes;
  // number of input units of this hidden layers. Equal to the number of output units of the previous layer.
  const int in_size;
  // number of output units of this hidden layers. Equal to the number of input units of the next layer.
  const int out_size;
};

#endif