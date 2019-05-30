///
///@file this file implement the identity activation function
#ifndef CS133_IDENTITY_HPP
#define CS133_IDENTITY_HPP

#include "../Layer.hpp"

/// @brief identity activation function
///
/// As child class of layer
class Identity : public Layer {
public:
	Identity();  ///< Default constructor
	~Identity();   ///< Destructor
	void init(int cur_in_size,
						int cur_input_row,
						int cur_input_col,
						int node_num,
						int kernel_row,
						int kernel_col,
						int stride_row,
						int stride_col,
						std::string padding,
						std::string name);   ///< Function of initialize the class
	void forward(std::vector<Eigen::MatrixXd> input);   ///< forward spread of the nework
};

#include "identity.hpp"

#endif // CS133_IDENTITY_HPP