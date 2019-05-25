// TO-DO
// The Sigmoid activation function
// a child class of layer
#ifndef CS133_SIGMOID_HPP
#define CS133_SIGMOID_HPP

#include "Layer.hpp"

class Sigmoid : public Layer{
 public:
  Sigmoid();
  ~Sigmoid();
  void init(Eigen::MatrixXd input_matrix);
  void forward();

 private:
 	size_t node_num;

 	Eigen::MatrixXd input;

 	Eigen::MatrixXd output;

 	const int in_size;

 	const int out_size;
}

#include "sigmoid.hpp"

#endif // CS133_RELU_HPP