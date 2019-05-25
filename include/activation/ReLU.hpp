// TO-DO
// The ReLU activation function
// a child class of layer
#ifndef CS133_RELU_HPP
#define CS133_RELU_HPP

#include "Layer.hpp"

// ReLU function:
// f(x) = max(x,0)
class Relu : public Layer{
 public:
  Relu();
  ~Relu();
  void init(Eigen::MatrixXd input_matrix);
  void forward();

 private:
 	size_t node_num;

 	Eigen::MatrixXd input;

 	Eigen::MatrixXd output;

 	const int in_size;

 	const int out_size;  
}

#include "reLU.hpp"

#endif // CS133_RELU_HPP