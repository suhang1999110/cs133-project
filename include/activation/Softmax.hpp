///@file ReLU.hpp
///@brief The Sigmoid activation function, a child class of layer
#ifndef CS133_SOFTMAX_HPP
#define CS133_SOFTMAX_HPP

#include "../Layer.hpp"

///@brief Class of Softmax activation function
///
/// f(xi) = (e^(xi))/(sigma e^(xj))
class Softmax : public Layer {
public:
	Softmax();   ///< Constructor
	~Softmax();  ///< Destructor
	void init(int cur_in_size,
						int cur_input_row,
						int cur_input_col,
						double node_num,
						double kernel_row,
						double kernel_col,
						double stride_row,
						double stride_col,
						std::string padding,
						std::string name);  ///<Initialize the Layer according to args
	void forward(std::vector<Eigen::MatrixXd> input);  ///< Spread forward to generate response
};

#include "softmax.hpp"

#endif // CS133_SOFTMAX_HPP