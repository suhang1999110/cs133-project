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
			  int non_arg1,
              int non_arg2,
              int non_arg3,
              int non_arg4,
              int non_arg5,
              std::string non_arg6,
			  std::string name);  ///<Initialize the Layer according to args
	void forward(std::vector<Eigen::MatrixXd> input);  ///< Spread forward to generate response
};

#include "softmax.hpp"

#endif // CS133_SOFTMAX_HPP