// TO-DO
// The Softmax activation function
// a child class of layer
#ifndef CS133_SOFTMAX_HPP
#define CS133_SOFTMAX_HPP

#include "../Layer.hpp"

class Softmax : public Layer {
public:
	Softmax();
	~Softmax();
	void init(int cur_in_size,
						int cur_input_row,
						int cur_input_col,
						double node_num,
						double kernel_row,
						double kernel_col,
						double stride_row,
						double stride_col,
						std::string padding,
						std::string name);
	void forward(std::vector<Eigen::MatrixXd> input);
};

#include "softmax.hpp"

#endif // CS133_SOFTMAX_HPP