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
              int non_arg1,
              int non_arg2,
              int non_arg3,
              int non_arg4,
              int non_arg5,
              std::string non_arg6,
			  std::string name);   ///< Function of initialize the class
	void forward(std::vector<Eigen::MatrixXd> input);   ///< forward spread of the nework
};

#include "identity.hpp"

#endif // CS133_IDENTITY_HPP