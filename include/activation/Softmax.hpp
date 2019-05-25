// TO-DO
// The Softmax activation function
// a child class of layer
#ifndef CS133_SOFTMAX_HPP
#define CS133_SOFTMAX_HPP

#include "Layer.hpp"

class Softmax : public Layer{
public:
	Softmax();
	~Softmax();
	void init(Eigen::MatrixXd input_matrix);
	void forward();

private:
	size_t node_num;

	Eigen::MatrixXd input;

	Eigen::MatrixXd output;

	const int in_size;

	const int out_size;
};

#include "softmax.hpp"

#endif // CS133_SOFTMAX_HPP